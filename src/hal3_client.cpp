/*
** client.c -- reads from a message queue
** g++ client.c mqueue.c -o client
*/
#include <stdio.h>
#include <stdlib.h>
#include "mqueue.h"

int main(void)
{
    mqueue client;

    printf("Client for message queue, use ctrl+c to exit.\n");
    client.set_queue_name("hal3.msg");
    client.start(false);
    int counter = 0;

    for(;;) {
        struct msgbuffer buf = client.get_buffer();

        if (!client.read(&buf)) {
            counter = counter + 1;

            if (counter > 250) {
                printf("Unable to read from mqueue server.\n");
                counter = 0;
            }
            client.start(false);
        }
        else if (buf.mtext[0] != 0) {
            /* Print message */
            printf("Message received: \"%s\"\n", buf.mtext);
            counter = 0;
        }

        /* Checking for messages each 10 milliseconds */
        usleep(20000);
    }

    return 0;
}
