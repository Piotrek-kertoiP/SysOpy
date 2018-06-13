//sender:

#define MAX_MESSAGE_LENGTH 128
#define SI_IPC_KEY_NUMBER 15
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int msg_q_id;
int msg_flags = IPC_CREAT | 0666;

struct message{
    long message_type;
    char text[MAX_MESSAGE_LENGTH];
};

int main(int argc, char** argv){
    key_t key = ftok( getenv("HOME"), SI_IPC_KEY_NUMBER );
    //alternatywnie: key_t key = 1234;

    msg_q_id = msgget(key, msg_flags);

    struct message wiadomosc;
    wiadomosc.message_type = 1;
    strcpy(wiadomosc.text, "Czesc\n");

    int msg_len = strlen(wiadomosc.text);

    msgsnd(msg_q_id, &wiadomosc, msg_len, IPC_NOWAIT);

    return 0;
}
