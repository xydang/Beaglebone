#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <string.h>

#define FALSE -1
#define TRUE 0

int speed_arr[] = { B38400, B19200, B9600, B4800, B2400, B1200, B600, B300, B38400, B19200, B9600, B4800, B2400, B1200, B600, B300 };
int  name_arr[] = { 38400,   19200,  9600,  4800,  2400,  1200,  600,  300,  38400,  19200,  9600,  4800,  2400,  1200,  600,  300 };

int serialfd;
char serial_buf[1024];

int serial_open(char* dev)
{    
    int fd = open( dev, O_RDWR | O_NOCTTY | O_NDELAY);

    if (fd == -1)
    {
        perror("Can't open the port!");
	return -1;
    }
    else
        return fd;
}

int serial_set_baud(int fd, int baud)
{
    if (fd == -1)
        return FALSE;
    int i;
    int status;
    struct termios Opt;
    tcgetattr(fd, &Opt);
    for (i = 0;  i < sizeof(speed_arr) / sizeof(int);  i++)
    {
        if (baud == name_arr[i])
        {
            tcflush(fd, TCIOFLUSH);
            cfsetispeed(&Opt, speed_arr[i]);
            cfsetospeed(&Opt, speed_arr[i]);
            status = tcsetattr(fd, TCSANOW, &Opt);
            if (status != 0)
                return FALSE;
            tcflush(fd,TCIOFLUSH); 
        }
    }
    return FALSE;
}

int serial_set_parity(int fd, int parity, int databits, int stopbits)
{
    struct termios options;
    if (tcgetattr(fd, &options) !=  0)
    {
       return FALSE;
    }
    options.c_cflag &= ~CSIZE;
    switch (databits)
    {
    case 7:
           options.c_cflag |= CS7;
           break;
    case 8:
           options.c_cflag |= CS8;
           break;
    default:    
           return FALSE;
    }
    
    switch (parity)
    {
    case 'n':
    case 'N':    
           options.c_cflag &= ~PARENB;   /* Clear parity enable */
           options.c_iflag &= ~INPCK;     /* Enable parity checking */ 
           break;
    case 'o':
    case 'O':
           options.c_cflag |= (PARODD | PARENB); /* odd */  
           options.c_iflag |= INPCK;             /* Disnable parity checking */
           break;
    case 'e':  
    case 'E':   
           options.c_cflag |= PARENB;     /* Enable parity */    
           options.c_cflag &= ~PARODD;   /* even */     
           options.c_iflag |= INPCK;       /* Disnable parity checking */
           break;
    case 'S': 
    case 's':  /*as no parity*/   
           options.c_cflag &= ~PARENB;
           options.c_cflag &= ~CSTOPB;
           break;
    default:
           return FALSE;
    }
    
    switch (stopbits)
    {   
    case 1:    
           options.c_cflag &= ~CSTOPB;  
           break;  
    case 2:
           options.c_cflag |= CSTOPB;
      break;
    default:
            return FALSE;
    }
    
    /* Set input parity option */
    if (parity != 'n' || parity != 'N')
        options.c_iflag |= INPCK;
    tcflush(fd,TCIFLUSH);
    options.c_cc[VTIME] = 150;
    options.c_cc[VMIN] = 0; 
    if (tcsetattr(fd,TCSANOW,&options) != 0)
    {
        return FALSE;
    }
    return TRUE;

}

