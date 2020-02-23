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
		printf("MQueue: Single message mode enabled %s\n",queue_file.c_str());
	} else {
		printf("MQueue: Multiple message mode %s \n",queue_file.c_str());
	}
}

/* Starting mqueue instance */
/**
 * 
 * param server_mode - true is sender, false = receiver
 * 
 */
int mqueue::start (bool server_mode)
{
	printf("MQueue: Start %s\n",queue_file.c_str());
	key_t key;

	/* Message queue's key */
	if ((key = ftok(queue_file.c_str(), 'B')) == -1) {
		perror("ftok");
		return -1;
	}

	/* Server mode creates the message queue structure, client mode requests access to queue */
    if (server_mode) {
		/* Server mode */
		if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
			return -1;
		}
	} else {
		/* Client mode */
		if ((msqid = msgget(key, 0644)) == -1) {
			return -1;
		}
	}
	return 0;
}

/* Write message to message queue */
bool mqueue::write (char* message)
{
	printf("MQueue: Write \n");

	bool retval = true;

	struct msgbuffer buf = get_buffer();
	std::strcpy(buf.mtext, message);

	/* Multiple message mode writes messages to queue without control*/
	if (single_message_mode) {
		/* Single message mode writes one message and waits for client to extract the data */
		if (get_num_messages () > 0) {
			printf("Flushing mqueue \n");
			flush_queue();
		}

		/* Using IPC_NOWAIT flag, msgsnd/msgrcv always return -1 with error code ENOMSG*/
		if (msgsnd(msqid, &buf, sizeof buf.mtext, IPC_NOWAIT) != -1) {

			int counter = 0;
			retval = true;
			while (get_num_messages() == 1) {

				if (counter == WAIT_MSECONDS) {
					/* Client dit not read the message, cleaning mqueue */
					flush_queue ();
					retval = false;
					break;
				}

				counter = counter + 1;
				
				/* Checking message's status for WAIT_MSECONDS milliseconds */
				usleep(1000);
			}
		}
	} else { 
		if (msgsnd(msqid, &buf, sizeof buf.mtext, 0) == -1) {
			perror("msgsnd");
			retval = false;
		}
	}

	return retval;
}

/* Read message from queue */
bool mqueue::read (msgbuffer *buf)
{
	/* Using IPC_NOWAIT flag, msgsnd/msgrcv always return -1 with error code ENOMSG */
	if (msgrcv(msqid, buf, sizeof buf->mtext, 0, MSG_NOERROR|IPC_NOWAIT) == -1) {
		if (errno != ENOMSG) {
			return false;
		}
	}

	return true;
}

/* Removes messages from queue */
void mqueue::flush_queue ()
{
	struct msgbuffer dummy_buf = get_buffer();

	while (get_num_messages() > 0) {
		msgrcv(msqid, &dummy_buf, sizeof dummy_buf.mtext, 0, MSG_NOERROR|IPC_NOWAIT);
	}
}

/* Get current number of messages stored in the queue */
int mqueue::get_num_messages ()
{
	struct msqid_ds ds;

	if (msgctl(msqid, IPC_STAT, &ds) == -1) {
		perror("msgctl");
		return -1;
	}

	return ds.msg_qnum;
}

/* Get amount of bytes stored in queue */
int mqueue::get_num_bytes ()
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

/* Remove message queue */
int mqueue::remove ()
{
	if (msgctl(msqid, IPC_RMID, NULL) == -1) {
		return -1;
	}

	return 0;
}
