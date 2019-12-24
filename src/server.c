/*
** server.c -- writes to a message queue
** g++ server.c mqueue.c -o server
*/
#include <stdio.h>
#include <stdlib.h>
#include "mqueue.h"

int main(void)
{
	mqueue server;

	server.set_queue_name("gimbal.msg");
	int msqid = server.start(true);

	/*false for multiple messages, true for single message mode*/
	server.set_single_message_mode(true);

	struct msgbuffer buf = server.get_buffer();

	printf("Enter to send data, ^D to quit:\n");

	while(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL) {

		printf("Message: \"%s\" \n", buf.mtext);	
		if(!server.write(msqid, buf)) {
			printf ("Write failed, client did not read the message \n");
		}
	}

	/* Removing message queue */
	if (msgctl(msqid, IPC_RMID, NULL) == -1) {
		perror("msgctl");
		exit(1);
	}

	return 0;
}
