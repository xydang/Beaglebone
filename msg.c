#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "json.h"
#include "reply.h"
#include "gpio.h"
#include "serial.h"

void msg_handle(char *msg_buf,int len)
{
	json_object *new_obj= json_tokener_parse(msg_buf);
	json_object *sub_obj= json_object_object_get(new_obj,"f");
	char *method=(char *)json_object_get_string(sub_obj);
	if(strcmp(method,"getAllSensors")==0){
		replay_sensor_list();
	}else if(strcmp(method,"updateSensor")==0){
		json_object *dev_obj= json_object_object_get(new_obj,"p1");
		json_object *val_obj= json_object_object_get(new_obj,"p2");
		if(strcmp(json_object_get_string(dev_obj),"sw0")==0){
			if(strcmp(json_object_get_string(val_obj),"1")==0){
				gpio_set(P8_12,0);
				printf("sw0 on.\n");	
			}else{
				gpio_set(P8_12,1);
				printf("sw0 off.\n");
			}
		}else if(strcmp(json_object_get_string(dev_obj),"sw1")==0){
			if(strcmp(json_object_get_string(val_obj),"1")==0){
				gpio_set(P8_14,0);
				printf("sw1 on.\n");	
			}else{
				gpio_set(P8_14,1);
				printf("sw1 off.\n");
			}
		}else if(strcmp(json_object_get_string(dev_obj),"sw2")==0){
			if(strcmp(json_object_get_string(val_obj),"1")==0){
				gpio_set(P8_16,0);
				printf("sw2 on.\n");	
			}else{
				gpio_set(P8_16,1);
				printf("sw2 off.\n");
			}
		}else if(strcmp(json_object_get_string(dev_obj),"sw3")==0){
			if(strcmp(json_object_get_string(val_obj),"1")==0){
				gpio_set(P8_18,0);
				printf("sw3 on.\n");	
			}else{
				gpio_set(P8_18,1);
				printf("sw3 off.\n");
			}
		}
		
		replay_sta(1,"ok");
		json_object_put(dev_obj);
		json_object_put(val_obj);
	}else if(strcmp(method,"writeSerial")==0){
		json_object *val_obj= json_object_object_get(new_obj,"p1");
		int n=strlen(json_object_get_string(val_obj));
		write(serialfd,json_object_get_string(val_obj),n);
		replay_sta(1,"ok");
		printf("write serial:%s\n",json_object_get_string(val_obj));
		json_object_put(val_obj);
	}else{
		printf("%s\n", json_object_to_json_string(new_obj));
		replay_sta(1,"ok");
	}
	json_object_put(new_obj);
	json_object_put(sub_obj);
}



