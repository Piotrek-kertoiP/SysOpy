GCC_FLAGS = -Wall
SENDER = ipc_queues_systemv_sender.c
RECEIVER = ipc_queues_systemv_receiver.c

all:	$(SENDER) $(RECEIVER)
	make sender
	make receiver
	

sender: $(SENDER)
	gcc $(GCC_FLAGS) $(SENDER) -o sender

receiver: $(RECEIVER)
	gcc $(GCC_FLAGS) $(RECEIVER) -o receiver

clean:
	rm sender receiver
