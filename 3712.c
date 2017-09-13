



#include "3712.h"

MODULE_LICENSE("GPL");


int init3712(void){


}

void SetDA(unsigned char channel,int value){



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
