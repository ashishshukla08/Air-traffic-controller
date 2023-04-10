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
#define console "operator"
#define DISPLAY_POINT "display"
#define ATTACH_POINT "myname"
#include <sys/neutrino.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dispatch.h>
typedef struct _pulse msg_header_t;

typedef struct _my_datac{

	    msg_header_t hdr;
	    int timer;

	}my_data_t_c;

int client_display(my_data_t_c msgc) {

	    int server_coid_display; //server connection ID.

	    if ((server_coid_display = name_open(console, 0)) == -1) {
	        return EXIT_FAILURE;
	    }

	    /* We would have pre-defined data to stuff here */
	    msgc.hdr.type = 0x00;
	    msgc.hdr.subtype = 0x01;

	    /* Do whatever work you wanted with server connection */

	if (MsgSend(server_coid_display, &msgc, sizeof(msgc), NULL, 0) == -1) {
																           perror("Error in communication");
																        }



	    /* Close the connection */
	    name_close(server_coid_display);
	    return EXIT_SUCCESS;
	}

int main(){
	my_data_t_c msgc;
	int f;
	while(1){
	printf("Enter the value n for 5 + n timer ");
	scanf("%d",&f);
	msgc.timer=f;
	client_display(msgc);
	}
	return 0;

}



