//timerInThread_modej.c
//gcc -o timerInThreadJ timerInThread_modej.c sm_car.c uart_setting.c -lpthread -lrt
/*common library*/
#include <stdio.h>
#include <stdlib.h>

/*pthread library*/
#include <pthread.h>

/*timer library*/
#include <sys/timerfd.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>        /* Definition of uint64_t */

/*error message*/
#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

void *myfunc (void *myvar);
void *myfunc2 (void *myvar);
void *timer (void *myvar);
void *timer2 (void *myvar);
static void print_elapsed_time(void);
int qq=0;

int main(int argc, char *argv[])
{

pthread_t thread1,thread2,thread3;
char *msg1 = "First thread";
char *msg2 ="Second thread";
char *msg3 ="three thread";
int ret1,ret2,ret3;
int count=1;
int *countP;
char *a="echo \"J2 90 5 12000;\" > /dev/ttyPS1";
countP=&count;
printf("main star\n");

//ret1 = pthread_create(&thread1,NULL,myfunc, (void*) msg1);
//ret2 = pthread_create(&thread2,NULL,timer2, (void*) msg2);
//ret3 = pthread_create(&thread3,NULL,timer2, (void*) msg3);
while(1)
{
ret3 = pthread_create(&thread3,NULL,timer2, (void*) msg3);
pthread_join(thread3,NULL);
uart_send_command(a);
printf("jjjjjj\n");
}


//pthread_join(thread1,NULL);
//pthread_join(thread2,NULL);
//pthread_join(thread2,NULL);

printf("m all over\n");

//printf("over =%d\n",ret2);
return 0;
}

void *myfunc (void *myvar)
{
char *msg;
msg = (char*)myvar;

int i;
for(i=0;i<10;i++)
{
qq++;
printf("%s %d q=%d \n",msg,i,qq);
usleep(1);
}
return NULL;
}


void *timer (void *myvar)
{
int *add;
add = (int*)myvar;
while(1){
printf("count =%d \n",qq);
usleep(10000);
qq+=*add;
if(qq==1000)break;
}
return NULL;
}

void *timer2 (void *myvar)
{
	struct itimerspec new_value;
	int max_exp, fd;
	struct timespec now;
	uint64_t exp, tot_exp;
	ssize_t s;
   
char *msg;
msg = (char*)myvar;

   int delaySec,delayNSec;
   int secAdd,nsecAdd;
   int addAllTime;
   
   delaySec=0;//延遲計算的秒數
   delayNSec=0;//延遲計算的奈秒數10000000ns==0.01sec
   secAdd=0;//每次增加的秒數
   nsecAdd=10000000;//每次增加的秒數10000000ns==0.01sec
   addAllTime=100;//計算的次數

   if (clock_gettime(CLOCK_REALTIME, &now) == -1)
       handle_error("clock_gettime");


   new_value.it_value.tv_sec = now.tv_sec + delaySec;	//延遲計算的秒數
   new_value.it_value.tv_nsec = now.tv_nsec + delayNSec;//延遲計算的奈秒數10000000ns==0.01sec
   new_value.it_interval.tv_sec = secAdd;					//每次增加的秒數
   new_value.it_interval.tv_nsec = nsecAdd;			//每次增加的秒數10000000ns==0.01sec
   max_exp = addAllTime;										//計算的次數

   

   fd = timerfd_create(CLOCK_REALTIME, 0);
   if (fd == -1)
       handle_error("timerfd_create");

   if (timerfd_settime(fd, TFD_TIMER_ABSTIME, &new_value, NULL) == -1)
       handle_error("timerfd_settime");

   print_elapsed_time();
   printf("%s timer started\n",msg);

   for (tot_exp = 0; tot_exp < max_exp;) {
       s = read(fd, &exp, sizeof(uint64_t));
       if (s != sizeof(uint64_t))
           handle_error("read");

       tot_exp += exp;
       print_elapsed_time();
       /*printf("read: %llu; total=%llu\n",
               (unsigned long long) exp,
               (unsigned long long) tot_exp);*/
   }
	printf("%s over \n",msg);
   
return NULL;
}

static void
print_elapsed_time(void)
{
   static struct timespec start;
   struct timespec curr;
   static int first_call = 1;
   int secs, nsecs;

   if (first_call) {
       first_call = 0;
       if (clock_gettime(CLOCK_MONOTONIC, &start) == -1)
           handle_error("clock_gettime");
   }

   if (clock_gettime(CLOCK_MONOTONIC, &curr) == -1)
       handle_error("clock_gettime");

   secs = curr.tv_sec - start.tv_sec;
   nsecs = curr.tv_nsec - start.tv_nsec;
   if (nsecs < 0) {
       secs--;
       nsecs += 1000000000;
   }
   //printf("%d.%03d: ", secs, (nsecs + 500000) / 1000000);
}