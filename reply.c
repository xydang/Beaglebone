#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "tcp.h"
#include "json.h"
#include "reply.h"
#include "gpio.h"

char send_buf[1024];

void reply_heart_beat()
{
	json_object *my_object = json_object_new_object();
	json_object_object_add(my_object, "method",json_object_new_string("update"));
	json_object_object_add(my_object, "gatewayNo",json_object_new_string(devno));
	json_object_object_add(my_object, "userkey", json_object_new_string(userid));
	strcpy(send_buf, json_object_to_json_string(my_object));
	strcat(send_buf,"&^!");
//	printf("my_object.to_string()=%s\n",send_buf);
	send(sockfd,send_buf,strlen(send_buf),0);
	json_object_put(my_object);
}

void replay_sta(int success,char *msg)
{
	json_object *my_object = json_object_new_object();
	json_object *sub_object=json_object_new_object();
	json_object_object_add(sub_object, "successful",json_object_new_boolean(success));
	json_object_object_add(sub_object, "message",json_object_new_string(msg));
	json_object_object_add(my_object, "method",json_object_new_string("response"));        
	json_object_object_add(my_object, "result",sub_object);

	strcpy(send_buf, json_object_to_json_string(my_object));
	strcat(send_buf,"&^!");
//	printf("my_object.to_string()=%s\n",send_buf);
	send(sockfd,send_buf,strlen(send_buf),0);
	json_object_put(my_object);
	json_object_put(sub_object);
}

void replay_sensor_list()
{
	json_object *my_object = json_object_new_object();
	json_object *my_array = json_object_new_array();
	json_object *sub_object=json_object_new_object();
	json_object *dev0_object=json_object_new_object();
	json_object *dev1_object=json_object_new_object();
	json_object *dev2_object=json_object_new_object();
	json_object *dev3_object=json_object_new_object();
	
	json_object_object_add(dev0_object, "id",json_object_new_string("sw0"));
	if(gpio_get(P8_12)==0)
		json_object_object_add(dev0_object, "value",json_object_new_string("1"));
	else
		json_object_object_add(dev0_object, "value",json_object_new_string("0"));
	json_object_object_add(dev1_object, "id",json_object_new_string("sw1"));
	if(gpio_get(P8_14)==0)
		json_object_object_add(dev1_object, "value",json_object_new_string("1"));
	else
		json_object_object_add(dev1_object, "value",json_object_new_string("0"));
	json_object_object_add(dev2_object, "id",json_object_new_string("sw2"));
	if(gpio_get(P8_16)==0)
		json_object_object_add(dev2_object, "value",json_object_new_string("1"));
	else
		json_object_object_add(dev2_object, "value",json_object_new_string("0"));
	json_object_object_add(dev3_object, "id",json_object_new_string("sw3"));
	if(gpio_get(P8_18)==0)
		json_object_object_add(dev3_object, "value",json_object_new_string("1"));
	else
		json_object_object_add(dev3_object, "value",json_object_new_string("0"));
	
	json_object_array_add(my_array,dev0_object);
	json_object_array_add(my_array,dev1_object);
	json_object_array_add(my_array,dev2_object);
	json_object_array_add(my_array,dev3_object);
	
	json_object_object_add(sub_object, "successful",json_object_new_boolean(1));
	json_object_object_add(sub_object, "message",json_object_new_string("ok"));
	json_object_object_add(sub_object, "data",my_array);

	json_object_object_add(my_object, "method",json_object_new_string("response"));
	json_object_object_add(my_object, "result",sub_object);

	strcpy(send_buf, json_object_to_json_string(my_object));
	strcat(send_buf,"&^!");
//	printf("my_object.to_string()=%s\n",send_buf);
	send(sockfd,send_buf,strlen(send_buf),0);

	json_object_put(my_object);
	json_object_put(my_array);
	json_object_put(sub_object);
	json_object_put(dev0_object);
	json_object_put(dev1_object);
	json_object_put(dev2_object);
	json_object_put(dev3_object);
}

void reply_update(int fd)
{

        char tmp_buf[8];
	int16_t temp=1,press=1;

//	temp=mpl3115_get_temp(fd);
//	press=mpl3115_get_press(fd);
        json_object *my_object = json_object_new_object();
        json_object *sensor_array = json_object_new_array();
        json_object *t1_object=json_object_new_object();
        json_object *p1_object=json_object_new_object();

        sprintf(tmp_buf,"%.1f",temp/10.0);
        json_object_object_add(t1_object,"Name",json_object_new_string("T1"));
        json_object_object_add(t1_object,"Value",json_object_new_string(tmp_buf));

        sprintf(tmp_buf,"%.1f",press/10.0);
        json_object_object_add(p1_object,"Name",json_object_new_string("P1"));
        json_object_object_add(p1_object,"Value",json_object_new_string(tmp_buf));

        json_object_array_add(sensor_array,t1_object);
        json_object_array_add(sensor_array,p1_object);

        json_object_object_add(my_object, "method",json_object_new_string("upload"));
        json_object_object_add(my_object, "data",sensor_array);

        strcpy(send_buf, json_object_to_json_string(my_object));
        strcat(send_buf,"&^!");
//      printf("my_object.to_string()=%s\n",send_buf);
        send(sockfd,send_buf,strlen(send_buf),0);
        json_object_put(my_object);
        json_object_put(sensor_array);
        json_object_put(t1_object);
        json_object_put(p1_object);



}




