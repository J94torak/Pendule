#ifndef __SENSOR__
#define __SENSOR__
#include<asm/io.h>
#include <asm/irq.h>
#include<linux/module.h>
#include<linux/init.h>
#include "3718.h"

u16 acquisition_angle(void);
u16 acquisition_position(void);
int initsensor(void);

#endif
