#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

int sockfd;
char tcp_buf[1024];

int tcp_open(char *server,int port)
{
  int fd;
	struct sockaddr_in server_addr;
	struct hostent *host;

	host=gethostbyname(server);
	if((fd=socket(AF_INET,SOCK_STREAM,0))==-1){
			fprintf(stderr,"socket error:%s\a\n",strerror(errno));
			exit(1);
	}
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(port);
	server_addr.sin_addr=*((struct in_addr *)host->h_addr);
	
	if(connect(fd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1){
			fprintf(stderr,"connect error:%s\a\n",strerror(errno));
			exit(1);
	}
  return fd;
}

