#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstdlib>
#include <unistd.h>

#define BUFFER_SIZE 200
#define WAIT_MSECONDS 50

struct msgbuffer {
	long mtype;
	char mtext[BUFFER_SIZE];
};

class mqueue {
	std::string queue_file;
	bool single_message_mode;
  public:
	mqueue ();
    int start (bool);
    void set_queue_name (std::string);
    void set_single_message_mode (bool mode);
	bool write (msgbuffer);
	bool read (msgbuffer*);
	int get_num_messages ();
	int get_num_bytes ();
	void flush_queue ();
	msgbuffer get_buffer ();
	int remove ();
  private:
    int msqid;
};
