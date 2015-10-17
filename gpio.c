#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include "gpio.h"

char export[64];

void gpio_export(int gpio)
{
	sprintf(export,"echo %d > /sys/class/gpio/export",gpio);
	system(export);
}

void gpio_init()
{
	gpio_export(P8_11);
	gpio_export(P8_12);
	gpio_export(P8_14);
	gpio_export(P8_15);
	gpio_export(P8_16);
	gpio_export(P8_17);
	gpio_export(P8_18);
	gpio_export(P8_26);
	gpio_export(P9_12);
	gpio_export(P9_15);
	gpio_export(P9_23);
	gpio_export(P9_25);
	gpio_export(P9_27);
	gpio_export(P9_42);
}

void gpio_dir(int gpio,int val)
{
	if(val)
		sprintf(export,"echo out > /sys/class/gpio/gpio%d/direction",gpio);
	else
		sprintf(export,"echo in > /sys/class/gpio/gpio%d/direction",gpio);
	system(export);
}

int gpio_get(int gpio)
{
	int fd,n;
	char val[8];

	sprintf(export,"/sys/class/gpio/gpio%d/value",gpio);
	fd=open(export,O_RDONLY);
	while(n=read(fd,val,8)>0);
	close(fd);
	if(val[0]==49)
		return 1;
	else
		return 0;
}

void gpio_set(int gpio,int val)
{
	if(val)
		sprintf(export,"echo 1 > /sys/class/gpio/gpio%d/value",gpio);
	else
		sprintf(export,"echo 0 > /sys/class/gpio/gpio%d/value",gpio);
	system(export);
}



