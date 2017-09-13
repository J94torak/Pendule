



#include "3712.h"

MODULE_LICENSE("GPL");


int init3712(void){
outb(0x80,PCM3712_OUT);
return 0;
}

void SetDA(unsigned char channel,int value){
int q=value/256;
int r=value%256;
if(channel==0x00){
outb(r&0xFF,PCM3712_DA0);
outb(q&0x0F,PCM3712_DA0+1);
outb(0xFF,PCM3712_SYNC);
}
else if(channel==0x01){
outb(r&0xFF,PCM3712_DA1);
outb(q&0x0F,PCM3712_DA1+1);
outb(0xFF,PCM3712_SYNC);
}

}


static int init_3712(void) {
  init3712();
  return 0;
}


static void exit_3712(void) {

}


module_init(init_3712);
module_exit(exit_3712);

EXPORT_SYMBOL(init3712);
EXPORT_SYMBOL(SetDA);
