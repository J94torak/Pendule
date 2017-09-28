#ifndef __CONTROLLER__
#define __CONTROLLER__
#include<asm/io.h>
#include <asm/irq.h>
#include<linux/module.h>
#include<linux/init.h>
#include "3718.h"
#include "3712.h"

#define POSITION0
#define POSITION90
#define ORIGIN
#define ANGLE_15
#define ANGLE15
#define ANGLE0
#define ANGLE_WIDTH 30.0
#define POSITION_WIDTH 90.5
void   init_control(double pposition0,double pposition90,double porigin, double pangle_15, double pangle15, double pangle0);
double commande(double position, double angle);
double conversionVoltToAngle(double angle);
double conversionVoltToPosition(double position);
double commandeVoltage(double angle, double position);




#endif
