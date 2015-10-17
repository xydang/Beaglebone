#ifndef __TCP_H__
#define __TCP_H__

int tcp_open(char *server,int port);

extern int sockfd;
extern char tcp_buf[1024];

#endif

