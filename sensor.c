
#include "sensor.h"

int initsensor(){
		ADRangeSelect(0x00,RANGE_5);
    ADRangeSelect(0x01,RANGE_10);
	  return 0;

}


u16 acquisition_angle(){
u16 voltage=0;

	if(SetChanel(0x00)!=0x00)
      printk("Angle:OK\n");
  else
      printk("Angle:NOK\n");
    voltage = ReadAD();
    printk("angle channel 0=%d\n",(unsigned int)voltage);
return	 voltage;

}

u16 acquisition_position(){
u16 voltage=0;
		if(SetChanel(0x01)!=0x00)
      printk("Position:OK\n");
  else
      printk("Position:NOK\n");
    voltage = ReadAD();
    printk("Position channel 1=%d\n",(unsigned int)voltage);
return voltage;    

}

static int init_sensor(void) {
  return initsensor();
}


static void exit_sensor(void) {

}

module_init(init_sensor);
module_exit(exit_sensor);

EXPORT_SYMBOL(acquisition_angle);
EXPORT_SYMBOL(acquisition_position);

