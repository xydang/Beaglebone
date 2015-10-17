#include <stdio.h>
#include <stdint.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include "mpl3115.h"

static int i2c_write(int fd,unsigned char addr,unsigned char reg,unsigned char data)
{
   unsigned char output_buffer[2];
   struct i2c_rdwr_ioctl_data packets;
   struct i2c_msg messages[1];

    messages[0].addr  = addr;
    messages[0].flags = 0;
    messages[0].len   = sizeof(output_buffer);
    messages[0].buf   = output_buffer;
    output_buffer[0] = reg;
    output_buffer[1] = data;
    packets.msgs  = messages;
    packets.nmsgs = 1;
    if(ioctl(fd, I2C_RDWR, &packets) < 0) {
        perror("Error sending data");
        return 1;
    }
    return 0;
}

static int i2c_read(int fd, unsigned char addr, unsigned char reg, unsigned char *data)
{
    unsigned char input_buffer, output_buffer;
    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[2];

    output_buffer = reg;
    messages[0].addr  = addr;
    messages[0].flags = 0;
    messages[0].len   = sizeof(output_buffer);
    messages[0].buf   = &output_buffer;
    messages[1].addr  = addr;
    messages[1].flags = I2C_M_RD;
    messages[1].len   = sizeof(input_buffer);
    messages[1].buf   = &input_buffer;
    packets.msgs      = messages;
    packets.nmsgs     = 2;
    if(ioctl(fd, I2C_RDWR, &packets) < 0) {
        perror("Error sending data");
        return 1;
    }
    *data = input_buffer;
    return 0;
}

int mpl3115_init()
{
	int fd;

	if ((fd = open("/dev/i2c-3", O_RDWR)) < 0){
		perror("error openning i2c-3!\n");
		exit(1);
	}
	i2c_write(fd,MPL3115_ADDR,MPL3115_CTRL_REG1,0x38);
	i2c_write(fd,MPL3115_ADDR,MPL3115_PT_DATA_CFG,0x07);
	i2c_write(fd,MPL3115_ADDR,MPL3115_CTRL_REG1,0x39);

	return fd;
}

uint8_t mpl3115_sta(int fd)
{
	uint8_t sta;
	
	i2c_read(fd,MPL3115_ADDR,0x00,&sta);
	if((sta&0x08)==0)
		return 1;
	else
		return 0;
}

int16_t mpl3115_get_press(int fd)
{
	uint8_t ah,ac,al;
	
	i2c_read(fd,MPL3115_ADDR,MPL3115_REG_P_MSB,&ah);
	i2c_read(fd,MPL3115_ADDR,MPL3115_REG_P_CSB,&ac);
	i2c_read(fd,MPL3115_ADDR,MPL3115_REG_P_LSB,&al);
	return ((ah<<10)+(ac<<2)+(al>>6))/10;
}

int16_t mpl3115_get_temp(int fd)
{
	uint8_t th,tl;
	i2c_read(fd,MPL3115_ADDR,MPL3115_REG_T_MSB,&th);
	i2c_read(fd,MPL3115_ADDR,MPL3115_REG_T_LSB,&tl);
	return (th*10+(tl>>4)*0.625);
}

int test() 
{
    int i2cfd;
    
    if ((i2cfd = open("/dev/i2c-3", O_RDWR)) < 0){
        perror("error openning i2c-3!\n");
        exit(1);
    }
    mpl3115_init(i2cfd);
    while(1){
	sleep(1);
        printf("temp=%d\t alt=%d\n",mpl3115_get_temp(i2cfd),mpl3115_get_press(i2cfd));
    }
    return 0;
}






