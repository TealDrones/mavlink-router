#include "mqueue.h"

/* Constructor */
mqueue::mqueue ()
{
	queue_file = "default.msg";
	single_message_mode = false;
}

/* Set message queue's file name */
void mqueue::set_queue_name (std::string file_name)
{	
	queue_file = file_name;
}

/* Set write mode: multiple or single message */
void mqueue::set_single_message_mode (bool mode)
{
	single_message_mode = mode;
	if (mode) {
		printf("MQueue: Single message mode enabled \n");
	} else {
		printf("MQueue: Multiple message mode \n");
	}
}

/* Starting mqueue instance */
int mqueue::start (bool server_mode)
{
	key_t key;
	int msqid;

	/* Message queue's key */
	if ((key = ftok(queue_file.c_str(), 'B')) == -1) {
		perror("ftok");
		return -1;
	}

	/* Server mode creates the message queue structure, client mode requests access to queue */
    if (server_mode) {
		/* Server mode */
		if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
			perror("msgget");
			return -1;
		}
	} else {
		/* Client mode */
		if ((msqid = msgget(key, 0644)) == -1) {
			perror("msgget");
			return -1;
		}
	}
	return msqid;
}

/* Write message to message queue */
bool mqueue::write (int msqid, msgbuffer buf)
{
	bool retval = true;

	/* Multiple message mode writes messages to queue without control*/
	if (!single_message_mode) {
		if (msgsnd(msqid, &buf, sizeof buf.mtext, 0) == -1) {
			perror("msgsnd");
			retval = false;
		}
	} else {
		/* Single message mode writes one message and waits for client to extract the data */
		if (get_num_messages (msqid) > 0) {
			printf("Flushing mqueue \n");
			flush_queue(msqid);
		}

		/* Using IPC_NOWAIT flag, msgsnd/msgrcv always return -1 with error code ENOMSG*/
		if (msgsnd(msqid, &buf, sizeof buf.mtext, IPC_NOWAIT) != -1) {

			int counter = 0;
			retval = true;
			while (get_num_messages(msqid) == 1) {

				if (counter == WAIT_MSECONDS) {
					/* Client dit not read the message, cleaning mqueue */
					flush_queue (msqid);
					retval = false;
					break;
				}

				counter = counter + 1;
				
				/* Checking message's status for WAIT_MSECONDS milliseconds */
				usleep(1000);
			}
		}
	}

	return retval;
}

/* Read message from queue */
bool mqueue::read (int msqid, msgbuffer *buf, int len)
{
	/* Using IPC_NOWAIT flag, msgsnd/msgrcv always return -1 with error code ENOMSG */
	if (msgrcv(msqid, buf, len, 0, MSG_NOERROR|IPC_NOWAIT) == -1) {
		if (errno != ENOMSG) {
			perror("msgrcv");
			return false;
		}
	}

	return true;
}

/* Removes messages from queue */
void mqueue::flush_queue (int msqid)
{
	struct msgbuffer dummy_buf = get_buffer();

	while (get_num_messages(msqid) > 0) {
		msgrcv(msqid, &dummy_buf, sizeof dummy_buf.mtext, 0, MSG_NOERROR|IPC_NOWAIT);
	}
}

/* Get current number of messages stored in the queue */
int mqueue::get_num_messages (int msqid)
{
	struct msqid_ds ds;

	if (msgctl(msqid, IPC_STAT, &ds) == -1) {
		perror("msgctl");
		return -1;
	}

	return ds.msg_qnum;
}

/* Get amount of bytes stored in queue */
int mqueue::get_num_bytes (int msqid)
{
	struct msqid_ds ds;

	if (msgctl(msqid, IPC_STAT, &ds) == -1) {
		perror("msgctl");
		return -1;
	}

	return ds.__msg_cbytes;
}

/* Create an empty msgbuffer */
msgbuffer mqueue::get_buffer ()
{
	msgbuffer buf;
	buf.mtype = 1;

	/* Initializing struct */
	for (int i = 0; i < BUFFER_SIZE; i++) {
		buf.mtext[i] = 0;
	}

	return buf;
}