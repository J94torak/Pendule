#include "3718.h"


int init3718(void){
outb(0x00,CONTROLE); 
outb(0x01,COUNT_EN);
return 0;
}

void SetChanel(unsigned char in_channel){
assert(in_channel<9);
unsigned char v_channel=in_channel<<4+in_channel;
outb(in_channel,MUX);
}
EXPORT_SYMBOL(SetChanel);

void ADRangeSelect(unsigned char channel,unsigned char range){
assert(range<9);
unsigned char v_channelBefore=inb(MUX)
SetChanel(channel);
outb(range,RANGE);
SetChanel(v_channelBefore);
}
EXPORT_SYMBOL(ADRangeSelect);

u16 ReadAD(void){
while(inb(STATUS)&0b10000000!=0b00000000);
outb(0xFF,R0);

while(inb(STATUS)&0b10010000!=0b00010000);

}
EXPORT_SYMBOL(ReadAD);


