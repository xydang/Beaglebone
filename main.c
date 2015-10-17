#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "tcp.h"
#include "reply.h"
#include "mpl3115.h"
#include "msg.h"
#include "gpio.h"
#include "serial.h"

char userid[36],devno[4];

void *task_recv(void *arg)
{
	int n=0;
	struct timespec ts = {0,10000};
	
	while(1){
		n=recv(sockfd,tcp_buf,1024,0);
		msg_handle(tcp_buf,n);
		memset(tcp_buf,0,n);
		n=0;
		nanosleep(&ts, NULL);
	}
}

void *task_send(void *arg)
{
	int n=29,k=9,i2cfd;

	//i2cfd=mpl3115_init(i2cfd);
	sleep(1);
	while(1){
		n++;
		k++;
		if(n>30){
			n=0;
			reply_heart_beat();
		}
		if(k>10){
			k=0;
			reply_update(i2cfd);
		}
		sleep(1);	
	}
	//close(i2cfd);
}

void sys_init()
{
	gpio_init();
	gpio_dir(P8_12,1);
	gpio_dir(P8_14,1);
	gpio_dir(P8_16,1);
	gpio_dir(P8_18,1);
	gpio_set(P8_12,1);
	gpio_set(P8_14,1);
	gpio_set(P8_16,1);
	gpio_set(P8_18,1);
	
	char *serial_dev = "/dev/ttyO0";
//	serialfd = serial_open(serial_dev);
//	serial_set_baud(serialfd, 115200);
//	serial_set_parity(serialfd, 'N', 8, 1);
}

int main(int argc,char *argv[])
{
	FILE *ffd;
	char server[32];
	int port;
	pthread_t thread_recv,thread_send;
	

	ffd=fopen("/home/debian/riot/iot.conf","r");
	if(ffd<0){
		printf("open /etc/iot.conf error!\n");
		exit(1);
	}
	fscanf(ffd,"userid=%s\ndevno=%s\nserver=%s\nport=%d\n",userid,devno,server,&port);	
	fclose(ffd);
	sys_init();

	sockfd=tcp_open(server,port);

	pthread_create(&thread_recv,NULL,task_recv,NULL);
	pthread_create(&thread_send,NULL,task_send,NULL);
	
	printf("\niot server started....\n");
	printf("server=%s\tport=%d\n\n",server,port);
	while(1){
		sleep(1);
	}
	close(sockfd);
	
	return 0;
}






