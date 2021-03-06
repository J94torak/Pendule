#ifndef __CONTROLLER__
#define __CONTROLLER__
#include<asm/io.h>
#include <asm/irq.h>
#include<linux/module.h>
#include<linux/init.h>
//Arcom22//Arcom12//Arcom21
#define POSITION0 8.09//7.263//9.03
#define POSITION90 -8.70//-9.534//-8.06
#define ORIGIN -0.57//-1.07//0.447
#define ANGLE_15 -3.78//-4.36// -3.63
#define ANGLE15 4.0//3.225//3.7
#define ANGLE0 -0.124//-0.48//0.004
#define ANGLE_WIDTH 30.0
#define POSITION_WIDTH 90.5
void   init_control(float pposition0,float pposition90,float porigin, float pangle_15, float pangle15, float pangle0);
float commande(float position, float angle);
float conversionVoltToAngle(float angle);
float conversionVoltToPosition(float position);
float commandeVoltage(float angle, float position);

#endif
