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
#define ATTACH_POINT "myname"
#define dis_point "display_plane"
#define console "operator"
#include <sys/neutrino.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dispatch.h>
#define ONE_THOUSAND 1000
#define ONE_MILLION 1000000
#define OFFSET 1000000
#define PERIOD 5000000


sigset_t sigst;
typedef struct _pulse msg_header_t;

typedef struct _my_datac{

	    msg_header_t hdr;
	    int timer;

	}my_data_t_c;

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
	    air sendarr[1200];


	}my_data_t;


/* Close the connection */
static void wait_next_activation(void) {
int dummy;
/* suspend calling process until a signal is pending */
sigwait(&sigst, &dummy);
}




int start_periodic_timer(uint64_t offset, int period) {
struct itimerspec timer_spec;
struct sigevent sigev;
timer_t timer;
const int signal = SIGALRM;
int res;
/* set timer parameters */
timer_spec.it_value.tv_sec = offset / ONE_MILLION;
timer_spec.it_value.tv_nsec = (offset % ONE_MILLION) * ONE_THOUSAND;
timer_spec.it_interval.tv_sec = period / ONE_MILLION;
timer_spec.it_interval.tv_nsec = (period % ONE_MILLION) * ONE_THOUSAND;
sigemptyset(&sigst); // initialize a signal set
sigaddset(&sigst, signal); // add SIGALRM to the signal set
sigprocmask(SIG_BLOCK, &sigst, NULL); //block the signal
/* set the signal event a timer expiration */
memset(&sigev, 0, sizeof(struct sigevent));
sigev.sigev_notify = SIGEV_SIGNAL;
sigev.sigev_signo = signal;

/* create timer */
res = timer_create(CLOCK_MONOTONIC, &sigev, &timer);

if (res < 0) {
perror("Timer Create");
exit(-1);
}

/* activate the timer */
return timer_settime(timer, 0, &timer_spec, NULL);
}

air arr[1200];
air badarr[1200];
double squareroot(double number) {
   double x = number;
   double y = 1;
   double precision = 0.00001; // set the precision level
   while (x - y > precision) {
       x = (x + y) / 2;
       y = number / x;
   }
   return x;
}
double* subt(double*a, double*b){
int i= 0;
double *c = malloc(sizeof(double)*3);
for(i=0;i<3;i++){
*(c+i)=a[i]-b[i];
}
return c;
}
double* dot_p(double e[],double o[]){
double *dot_product = malloc(sizeof(double)*3);
*dot_product = e[0]*o[0] +  e[1]*o[1] +  e[2]*o[2];
// printf("------%lf----",*dot_product);
// int d1,d2,d3;
// d1 = (e[0])*(o[0]);
// d2 = e[1]*o[1];
// d3 = e[2]*o[2];
//    printf("DOT %lf ", *dot_product);
return dot_product;
}

int* radar(air arr[]) {
    my_data_t msg;

	    int server_coid; //server connection ID.

	    if ((server_coid = name_open(ATTACH_POINT, 0)) == -1) {
	        return EXIT_FAILURE;
	    }
	    /* We would have pre-defined data to stuff here */
msg.hdr.type = 0x00;
msg.hdr.subtype = 0x01;
double p1[3] = {100000,0,15000};
double p2[3] = {0,0,15000};
double p4[3] = {100000,100000,15000};
double p5[3] = {100000,0,40000};
int i=0;

double pv[7]={arr->x,arr->y,arr->z,arr->id,arr->x_speed,arr->y_speed,arr->z_speed};

double *s = malloc(sizeof(double)*3);
s =(subt(p2,p1));
// printf("\n\n subtraction result %lf,%lf,%lf\n",*(s),*(s+1) ,*(s+2));
double *j;
j =(subt(p4,p1));
double *k;
k =(subt(p5,p1));
double *v = malloc(sizeof(double)*3);
v = subt(pv,p1);
// printf("%lf---- %lf---- %lf vs",*v,*(v+1),*(v+2));
  double *dot_vs =malloc(sizeof(double)*3) ;
  double *dot_vj;
  double *dot_vk;
double *dot_ii =malloc(sizeof(double)*3);
double *dot_jj =malloc(sizeof(double)*3);
double *dot_kk =malloc(sizeof(double)*3);
  dot_vs= dot_p(v,s);
  dot_vj=dot_p(v,j);
  dot_vk=dot_p(v,k);
dot_ii=dot_p(s,s);
dot_jj=dot_p(j,j);
dot_kk=dot_p(k,k);
if( ((0<=*dot_vs) && (*dot_vs<=*dot_ii)) && ((0<=*dot_vj) && (*dot_vj<=*dot_jj))&& ((0<=*dot_vk) && (*dot_vk<=*dot_kk)))
{

printf("\n Plane is within Radar zone\n");


msg.sendarr[i].id=pv[3];
msg.sendarr[i].x=pv[0];
msg.sendarr[i].y=pv[1];
msg.sendarr[i].z=pv[2];
msg.sendarr[i].x_speed=pv[4];
msg.sendarr[i].y_speed=pv[5];
msg.sendarr[i].z_speed=pv[6];



for(int i=0;i<=1200;i++){

				double xsq = (badarr[i].x-pv[0])*(badarr[i].x-pv[0]);
				double ysq = (badarr[i].y-pv[1])*(badarr[i].y-pv[1]);
	double zsq = (badarr[i].z-pv[2])*(badarr[i].z-pv[2]);
     double stand = xsq+ysq+zsq;
						float f =squareroot(stand);
						double height_two_points = (badarr[i].z-pv[2]);
				height_two_points = abs(height_two_points);
//				printf("HEIGHT BTW 2 PLANES %lf\n",height_two_points);
				if(height_two_points<1000){
									double distance_two_points=xsq+ysq;
									float dist_tp = squareroot(distance_two_points);
//									printf("\n----------plane in z-------------%lf\n",dist_tp);
									if(dist_tp<3000){
														int collision_id =(badarr[i].id);
														printf("\nCollission-----------------ID %d between ID %d  \n",(int)pv[3],collision_id);
														strcpy(msg.coll,"Collission");
														msg.id_1 = (int)pv[3];
														msg.id_2 = collision_id;
									if (MsgSend(server_coid, &msg, sizeof(msg), NULL, 0) == -1) {
//															           perror("Error in communication");
															        }
													}
				}
}
if (MsgSend(server_coid, &msg, sizeof(msg), NULL, 0) == -1) {
															           perror("Error in communication");
															        }

	    name_close(server_coid);

		return 0;
	}


}

int server() {
	int i=0;
   name_attach_t *attach;
   my_data_t msg;
   int rcvid;
   my_data_t_c msgc;

   /* Create a local name (/dev/name/local/...) */
   if ((attach = name_attach(NULL, console, 0)) == NULL) {
       return EXIT_FAILURE;
   }

   /* Do your MsgReceive's here now with the chid */
   while (1) {
	   int timer ;
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
              printf("Display Collssion detected between %d \n", msgc.timer);
              int timer = 0;
              timer = msgc.timer;
//              printf("pppppppppppppppppppppppppppppp %d %d %d %d\n ", msg.sendarr[0].id, msg.sendarr[0].x, msg.sendarr[0].z, msg.sendarr[0].y);
              return timer;

	      }
	   }
       MsgReply(rcvid,EOK,0,0);
       break;
   }


   }

int main(void){
float dist_p_p1,dist_p_p2,dist_p_p3;
float time =5;
printf("HELLO");
air arr[1200];
my_data_t_c msgc;
pthread_t thread_radar[1200];
int arr1[2];
   FILE* fp = fopen("/data/home/root/sample.csv", "r");
   int i=0;
        int read = 0;

   if (!fp)
       printf("Can't open file\n");
   else {
    do{
    read =fscanf(fp,"%d,%d,%d,%d,%d,%d,%d\n",&arr[i].id,&arr[i].x,&arr[i].y,&arr[i].z,&arr[i].x_speed,&arr[i].y_speed,&arr[i].z_speed);

    if(read==7) i++;
    if (ferror(fp))
       {
         printf("Error reading file.\n");
         return 1;
       }
    }
    while(!feof(fp));
    fclose(fp);
                int res;


                              //set and activate a timer
                                    res = start_periodic_timer(OFFSET, PERIOD);
//                                    if (res < 0 ){
//                                    perror("Start periodic timer");
//                                    return -1;
//                                    }


                                    while (1) {
                                    	int a =server();
                                    	if(a==0){

                                    		start_periodic_timer(5000000000, 5000000000);

                                    	}
                                    	else{
                                    		start_periodic_timer(50000000, a);
                                    	}





                                    	//wait for timer expiration

                                    	wait_next_activation();
                                    for (int j = 0; j < 1200; j++){
//                                              printf("%d %d %d %d %d %d %d\n", arr[j].id,arr[j].x,arr[j].y,arr[j].z,arr[j].x_speed,arr[j].y_speed,arr[j].z_speed);
                                               dist_p_p1 = (arr[j].x_speed)*time;
                                               dist_p_p2= (arr[j].y_speed)*time;
                                               dist_p_p3 = (arr[j].z_speed)*time;
                                              pthread_create(&thread_radar[j],NULL,radar,&arr[j]);
                                              pthread_join(thread_radar[j], NULL);
                                                  //executes the task
                                              	   badarr[j]=arr[j];
                                                   arr[j].x = dist_p_p1 + arr[j].x;
                                                   arr[j].y = dist_p_p2 + arr[j].y;
                                                   arr[j].z = dist_p_p3 + arr[j].z;
//                                                 printf("\n\n ----------timer air %d, /*-d, %d-----------\n\n",arr[j].x,arr[j].y,arr[j].z);
                                    }
         printf("\n");
       }
     printf("array ----%d------", arr);
   }
   return 0;
}




