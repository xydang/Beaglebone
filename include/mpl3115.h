#ifndef __MPL_3115_H__
#define __MPL_3115_H__

//#define MPL3115_ADDR              0xC0   //8bit addr
#define MPL3115_ADDR              0x60   //7bit addr
#define MPL3115_REG_STATUS        0x00   //Alias for DR_STATUS or F_STATUS
#define MPL3115_REG_P_MSB         0x01   //Pressure Data Out MSB,Bits 12-19
#define MPL3115_REG_P_CSB         0x02   //Bits 4-11 of 20-bit real-time Pressure sample
#define MPL3115_REG_P_LSB         0x03   //Bits 0-3 of 20-bit real-time Pressure sample
#define MPL3115_REG_T_MSB         0x04   //Bits 4-11 of 12-bit real-time Temperature sample
#define MPL3115_REG_T_LSB         0x05   //Bits 1-3 of 12-bit real-time Temperature sample
#define MPL3115_REG_DR_STATUS     0x06   //Data Ready status information 
#define MPL3115_PT_DATA_CFG       0x13   //Data event flag configuration
#define MPL3115_CTRL_REG1         0x26   //Modes, Oversampling
#define MPL3115_CTRL_REG2         0x27   //Acquisition time step
#define MPL3115_CTRL_REG3         0x28   //Interrupt pin configuration
#define MPL3115_CTRL_REG4         0x29   //Interrupt enables
#define MPL3115_CTRL_REG5         0x2A   //Interrupt output pin assignment
#define MPL3115_OFFSET_P          0x2B   //Pressure data offset 
#define MPL3115_OFFSET_T          0x2C   //Temperature data offset
#define MPL3115_OFFSET_H          0x2D   //Altitude data offset

int mpl3115_init();
uint8_t mpl3115_sta(int fd);
int16_t mpl3115_get_press(int fd);
int16_t mpl3115_get_temp(int fd);

#endif

