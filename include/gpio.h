#ifndef __GPIO_H__
#define __GPIO_H__

#define GPIO0_7   7
#define GPIO0_26  26
#define GPIO0_27  27
#define GPIO1_12  44
#define GPIO1_13  45
#define GPIO1_14  46
#define GPIO1_15  47
#define GPIO1_16  48
#define GPIO1_17  49
#define GPIO1_28  60
#define GPIO1_29  61
#define GPIO2_1   65
#define GPIO3_21  117
#define GPIO3_19  115

#define P8_11 GPIO1_13
#define P8_12 GPIO1_12
#define P8_14 GPIO0_26
#define P8_15 GPIO1_15
#define P8_16 GPIO1_14
#define P8_17 GPIO0_27
#define P8_18 GPIO2_1
#define P8_26 GPIO1_29

#define P9_12 GPIO1_28
#define P9_15 GPIO1_16
#define P9_23 GPIO1_17
#define P9_25 GPIO3_21
#define P9_27 GPIO3_19
#define P9_42 GPIO0_7


void gpio_init();
void gpio_dir(int gpio,int dir);
void gpio_set(int gpio,int value);
int gpio_get(int gpio);

#endif


