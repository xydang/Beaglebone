#ifndef __SERIAL_H__
#define __SERIAL_H__

int serial_open(char* dev);
int serial_set_baud(int fd, int baud);
int serial_set_parity(int fd, int parity, int databits, int stopbits);

extern int serialfd;
extern char serial_buf[1024];

#endif
