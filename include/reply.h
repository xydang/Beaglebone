#ifndef __REPLAY_H__
#define __REPLAY_H__

void reply_heart_beat();
void replay_sta(int success,char *msg);
void replay_sensor_list();
void reply_update(int fd);

extern char send_buf[1024];
extern char userid[36];
extern char devno[4];
#endif
