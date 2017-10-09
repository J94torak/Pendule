



#include "3718.h"

MODULE_LICENSE("GPL");

int init3718(void){
outb(0x00,CONTROLE); 
outb(0x01,COUNT_EN);
return 0;
}

int SetChanel(unsigned char in_channel){
unsigned char v_channel=(in_channel<<4)+in_channel;
if(in_channel>9)
  return -1;
outb(v_channel,MUX);
return (int)(ReadChannel()==(u8)in_channel);
}


int ADRangeSelect(unsigned char channel,unsigned char range){
unsigned char v_channelBefore=inb(MUX);
if(channel>9)
  return -1;
SetChanel(channel);
outb(range,RANGE);
SetChanel(v_channelBefore&0x0F);
return 0;
}


u16 ReadAD(void){
while((inb(STATUS2)&0x80)!=0x00);
outb(0xFF,R0);
while((inb(STATUS2)&0x90)!=0x10);
return (u16)((inb(R0)>>4)|(inb(R1)<<4));
}


u8 ReadChannel(void){
while((inb(STATUS2)&0x80)!=0x00);
outb(0xFF,R0);
while((inb(STATUS2)&0x90)!=0x10);
printk("Channel=%d\n",((int)(inb(R0)&(0x0F))));
return (u8)(inb(R0)&(0x0F));
}

float valueToVoltagePolar(int vRef, int value){

return ((float)vRef)*(((float)value)-2048.0)/2048.0;

}

float valueToVoltageUniPolar(int vRef, int value){

return ((float)vRef)*2.0*((float)value)/4096.0;

}

static int init_3718(void) {
  init3718();
  return 0;
}


static void exit_3718(void) {

}
module_init(init_3718);
module_exit(exit_3718);

EXPORT_SYMBOL(SetChanel);
EXPORT_SYMBOL(ADRangeSelect);
EXPORT_SYMBOL(ReadAD);
EXPORT_SYMBOL(ReadChannel);
EXPORT_SYMBOL(valueToVoltagePolar);
EXPORT_SYMBOL(valueToVoltageUniPolar);
