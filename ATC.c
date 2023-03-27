#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <math.h>
#include <fenv.h>

typedef struct {
	int id;
	int x;
		int y;
		int z;
		int x_speed;
		int y_speed;
		int z_speed;
	} air;
	air arr[100];
	air badarr[100];
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
//	printf("------%lf----",*dot_product);
// 	int d1,d2,d3;
// 	d1 = (e[0])*(o[0]);
// 	d2 = e[1]*o[1];
// 	d3 = e[2]*o[2];
//    printf("DOT %lf ", *dot_product);
	return dot_product;
}
int* radar(air arr[]) {
	double p1[3] = {100000,0,15000};
	double p2[3] = {0,0,15000};
	double p4[3] = {100000,100000,15000};
	double p5[3] = {100000,0,40000};

	double pv[3]={arr->x,arr->y,arr->z};
	    printf("\X in Radar====%lf ==\n",pv[0]);
	     printf("\Y in Radar====%lf ==\n",pv[1]);
		    printf("\Z in Radar====%lf ==\n",pv[2]);

		    			printf("bbbbbbbbbbbbb--- %d\n",badarr[10].x);
		    	    	printf("bbbbbbbbbbbbb--- %d\n",badarr[10].y);
		    	    	printf("bbbbbbbbbbbbb--- %d\n",badarr[10].z);
	double *s = malloc(sizeof(double)*3);
	s =(subt(p2,p1));
//	printf("\n\n subtraction result %lf,%lf,%lf\n",*(s),*(s+1) ,*(s+2));
	double *j;
	j =(subt(p4,p1));
	double *k;
	k =(subt(p5,p1));
	double *v = malloc(sizeof(double)*3);
	v = subt(pv,p1);
//	printf("%lf---- %lf---- %lf vs",*v,*(v+1),*(v+2));
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

		printf("\n Plane is within Radar zone");

		for(int i=0;i<=20;i++){
					printf("Badarrrrrrr[%d],%d,%d,%d",i,badarr[i].x,badarr[i].y,badarr[i].z);

     double stand = (((badarr[i].x-pv[0])*(badarr[i].x-pv[0]))+((badarr[i].y-pv[1])*(badarr[i].y-pv[1]))+((badarr[i].z-pv[2])*(badarr[i].z-pv[2])));
						float f =squareroot(stand);
						printf("\nSTAND %lf\n", stand);
						printf("\n\n\n TOTAL DISTANCE BETWEEN TWO PLANES %f\n\n\n",f);

			if(pv[0]==badarr[i].x){
	double distance_two_points=(((badarr[i].y-pv[1])*(badarr[i].y-pv[1]))+((badarr[i].z-pv[2])*(badarr[i].z-pv[2])));
			float dist_tp = squareroot(distance_two_points);
				printf("\n----------plane in x-------------%lf\n",dist_tp);
				if(dist_tp>3000){
					printf("\nSAFE DISTANCE YOU CAN GO AHEAD\n");
				}
				else{
					printf("\nPLEASE CHANGE THE DISTANCE BETWEEN 2\n");
				}
			}

			else if(pv[1]==badarr[i].y){
				double distance_two_points=(((badarr[i].x-pv[0])*(badarr[i].x-pv[0]))+((badarr[i].z-pv[2])*(badarr[i].z-pv[2])));
				float dist_tp = squareroot(distance_two_points);
				printf("\n----------plane in y-------------%lf\n",dist_tp);
				if(dist_tp>3000){
									printf("\nSAFE DISTANCE YOU CAN GO AHEAD\n");
								}
								else{
									printf("\nPLEASE CHANGE THE DISTANCE BETWEEN 2\n");
								}
			}

			else if(pv[2]==badarr[i].z){
				double distance_two_points=(((badarr[i].y-pv[1])*(badarr[i].y-pv[1]))+((badarr[i].x-pv[0])*(badarr[i].x-pv[0])));
				float dist_tp = squareroot(distance_two_points);
				printf("\n----------plane in z-------------%lf\n",dist_tp);
				if(dist_tp>3000){
									printf("\nSAFE DISTANCE YOU CAN GO AHEAD\n");
								}
								else{
									printf("\nPLEASE CHANGE THE DISTANCE BETWEEN 2\n");
								}
			}

			else{
				double height_two_points = (badarr[i].z-pv[2]);
				height_two_points = abs(height_two_points);
				printf("HEIGHT BTW 2 PLANES %lf\n",height_two_points);
				if(height_two_points>1000){
					printf("\n-------------SAFE, YOU CAN GO AHEAD----------");

				}
				else{
					printf("\n---------------PLEASE CHANGE THE HEIGHT------------");
				}
			}

		}
	}
		else
		{
			printf("\n \n Plane is out of zone");
		}

		return 0;
	}

int main(void){
	printf("HELLO");
		air arr[100];
		 air thread_args[1000];
		pthread_t thread_radar[1000];
		    FILE* fp = fopen("/data/home/root/sample.csv", "r");
		    int i=0;
		    	    	int read = 0;

		    if (!fp)
		        printf("Can't open file\n");
		    else {

		    	do{
		    	read =fscanf(fp,"%d,%d,%d,%d\n",&arr[i].id,&arr[i].x,&arr[i].y,&arr[i].z);
		    	badarr[i]= arr[i];
		    	if(read==4) i++;
		    	 if (ferror(fp))
		        {
		          printf("Error reading file.\n");
		          return 1;
		        }
		    	}while(!feof(fp));
		    	fclose(fp);
		    	for (int j = 0; j < i; j++){
		    		        printf("%d %d %d %d \n", arr[j].id,arr[j].x,arr[j].y,arr[j].z );
		    		        pthread_create(&thread_radar[j],NULL,radar,&arr[j]);
		    		            	pthread_join(thread_radar[j], NULL);
		    		      printf("\n");
		        }
			      printf("array ----%d------", arr);
		    }
		    return 0;
}
