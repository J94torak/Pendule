#ifndef __CONTROLLER__
#define __CONTROLLER__
#include<asm/io.h>
#include <asm/irq.h>
#include<linux/module.h>
#include<linux/init.h>
//#include <rtai_fifos.h>
#include "3718.h"
#include "3712.h"
//Arcom21
#define POSITION0 8.18
#define POSITION90 -8.62
#define ORIGIN -0.31
#define ANGLE_15 -4.3
#define ANGLE15 3.32
#define ANGLE0 -0.47
#define ANGLE_WIDTH 30.0
#define POSITION_WIDTH 90.5
void   init_control1(float pposition0,float pposition90,float porigin, float pangle_15, float pangle15, float pangle0);
float commande1(float position, float angle);
float conversionVoltToAngle1(float angle);
float conversionVoltToPosition1(float position);
float commandeVoltage1(float angle, float position);




#endif
