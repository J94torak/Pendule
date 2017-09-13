



#include "3712.h"

MODULE_LICENSE("GPL");

 void PCM3712setda0(unsigned value){



}

 void PCM3712setda1(unsigned value){


}

unsigned PCM3712VBitoValue(float vref, float V){


}
unsigned PCM3712VUnitoValue(float vref, float V){



}

static int init_3712(void) {
  init3712();
  return 0;
}


static void exit_3712(void) {

}
module_init(init_3712);
module_exit(exit_3712);

EXPORT_SYMBOL(SetChanel);
EXPORT_SYMBOL(ADRangeSelect);
EXPORT_SYMBOL(ReadAD);
EXPORT_SYMBOL(ReadChannel);
