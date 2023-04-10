#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dispatch.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <math.h>
#include <fenv.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#define DISPLAY_POINT "display"
#define ATTACH_POINT "myname"
#include <sys/neutrino.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dispatch.h>
typedef struct _pulse msg_header_t;

/* This is the name that will be used by the server to create a channel and used by
 * the client to connect to the appropriated channel */


typedef struct {
	 msg_header_t hdr;
int id;
int x;
int y;
int z;
int x_speed;
int y_speed;
int z_speed;
} air;
typedef struct _my_data {

	    msg_header_t hdr;
	    int id;
	    int id_1;
	    int id_2;
	    int id_3;
	    char coll[20];
	    air sendarr[100];


	}my_data_t;

air computer_arr[100];


/* We specify the header as being at least a pulse */
/* All of your messages should start with this header */
/* This struct contains a type/subtype field as the first 4 bytes.
 * The type and subtype field can be used to identify the message that is being received.
/ * This allows you to identify data which isn't destined for your server. */



/* Our real data comes after the header */

/*** Server Side of the code ***/
int server() {
	int i=0;
   name_attach_t *attach;
   my_data_t msg;
   int rcvid;

   /* Create a local name (/dev/name/local/...) */
   if ((attach = name_attach(NULL, DISPLAY_POINT, 0)) == NULL) {
       return EXIT_FAILURE;
   }

   /* Do your MsgReceive's here now with the chid */
   while (1) {

   	   /* Server will block in this call, until a client calls MsgSend to send a message to
   	    * this server through the channel named "myname", which is the name that we set for the channel,
   	    * i.e., the one that we stored at ATTACH_POINT and used in the name_attach call to create the channel. */
       rcvid = MsgReceive(attach->chid, &msg, sizeof(msg), NULL);

	   /* In the above call, the received message will be stored at msg when the server receives a message.
	    * Moreover, rcvid */

       if (rcvid == -1) {/* Error condition, exit */
           break;
       }

       if (rcvid == 0) {/* Pulse received */
           switch (msg.hdr.code) {
           case _PULSE_CODE_DISCONNECT:
               /*
                * A client disconnected all its connections (called
                * name_close() for each name_open() of our name) or
                * terminated
                */
               ConnectDetach(msg.hdr.scoid);
               break;
           case _PULSE_CODE_UNBLOCK:
               /*
                * REPLY blocked client wants to unblock (was hit by
                * a signal or timed out).  It's up to you if you
                * reply now or later.
                */
               break;
           default:
               /*
                * A pulse sent by one of your processes or a
                * _PULSE_CODE_COIDDEATH or _PULSE_CODE_THREADDEATH
                * from the kernel?
                */
               break;
           }
           continue;
       }

       /* name_open() sends a connect message, must EOK this */
       if (msg.hdr.type == _IO_CONNECT ) {
           MsgReply( rcvid, EOK, NULL, 0 );
           continue;
       }

       /* Some other QNX IO message was received; reject it */
       if (msg.hdr.type > _IO_BASE && msg.hdr.type <= _IO_MAX ) {
           MsgError( rcvid, ENOSYS );
           continue;
       }

//	   /* Here are the messages that you will work on, i.e., messages that will have a meaning
	   if (msg.hdr.type == 0x00) {
	      if (msg.hdr.subtype == 0x01) {
              /* A message (presumable ours) received, handle */
              printf("Display Collssion detected between %d and %d \n", msg.id_1,msg.id_2);
//              printf("pppppppppppppppppppppppppppppp %d %d %d %d\n ", msg.sendarr[0].id, msg.sendarr[0].x, msg.sendarr[0].z, msg.sendarr[0].y);

	      }
	   }
       MsgReply(rcvid,EOK,0,0);
   }
       return EXIT_SUCCESS;

   }

int main(int argc, char **argv) {


int ret;

        printf("Running DISPLAY ... \n");
        ret=server();   /* see name_attach() for this code */
	return ret;



}
