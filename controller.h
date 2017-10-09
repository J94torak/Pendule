#ifndef __CONTROLLER__
#define __CONTROLLER__
#include<asm/io.h>
#include <asm/irq.h>
#include<linux/module.h>
#include<linux/init.h>
#include <rtai_fifos.h>
#include "3718.h"
#include "3712.h"

#define POSITION0 0
#define POSITION90 0
#define ORIGIN 0 
#define ANGLE_15 0 
#define ANGLE15 0
#define ANGLE0 0
#define ANGLE_WIDTH 30.0
#define POSITION_WIDTH 90.5
void   init_control(float pposition0,float pposition90,float porigin, float pangle_15, float pangle15, float pangle0);
float commande(float position, float angle);
float conversionVoltToAngle(float angle);
float conversionVoltToPosition(float position);
float commandeVoltage(float angle, float position);




#endif
