#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>

#define FREE_TABLES 15

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int tables;
int sem_id;
struct sembuf *sops;
union semun sem_info;

int book_tables(int desired_amount){
    if( desired_amount > 0){
        int old_sem_op_val = semctl( sem_id, 0, GETVAL, 0);

        sops -> sem_num = 0;
        sops -> sem_op =  -1;
        sops -> sem_flg = IPC_NOWAIT;

        for(int i=0; i< desired_amount; i++){
            semop(sem_id, sops, 1);
        }

        int new_sem_op_val = semctl( sem_id, 0, GETVAL, 0);
        return old_sem_op_val - new_sem_op_val;
    }
    else{
        sops -> sem_num = 0;
        sops -> sem_op =  (-1)*desired_amount;
        sops -> sem_flg = IPC_NOWAIT;

        semop(sem_id, sops, 1);

        if( semctl(sem_id, 0, GETVAL, 0 ) > FREE_TABLES) semctl(sem_id, 0, SETVAL, sem_info);
        return desired_amount;
    }   
}

int main(){
    char* pathname = getenv("HOME");
    int proj = 100;

    key_t sem_key = ftok(pathname, proj);

    sem_id = semget(sem_key, 1, IPC_CREAT | S_IRWXU);

    sem_info.val = FREE_TABLES;

    semctl(sem_id, 0, SETVAL, sem_info);

    sops = malloc(sizeof(struct sembuf));

    while(1){
        printf("How many tables you wish to book?\n");
        scanf("%d", &tables);
        printf("You want to book %d tables\n", tables);
        if( tables == 0 ) 
        {
            printf("See you again!\n");
            break;
        }

        int booked_tables = book_tables(tables);

        if( booked_tables == tables ){
            int tables_available = semctl(sem_id, 0, GETVAL, 0);
            if( tables > 0) 
                printf("All %d tables are now booked for you\n", tables);
            else
                printf("You free %d tables\n", tables*(-1));
            printf("There's %d tables available\n", tables_available);
        }
        else 
            printf("There's not enough tables in our restaurant. %d tables were booked\n", booked_tables);
    }

    semctl(sem_id, 0, IPC_RMID);

    exit(0);
}