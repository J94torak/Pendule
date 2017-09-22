#ifndef __CONTROLLER__
#define __CONTROLLER__
#include<asm/io.h>
#include <asm/irq.h>
#include<linux/module.h>
#include<linux/init.h>
void   init_control(double pposition0,double pposition85, double pangle_15, double pangle15);
double commande(double position, double angle);
double conversionVoltToAngle(double angle);
double conversionVoltToPosition(double position);
double commandeVoltage(double angle, double position);

#endif
