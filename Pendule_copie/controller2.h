#ifndef __CONTROLLER__
#define __CONTROLLER__
#include<asm/io.h>
#include <asm/irq.h>
#include<linux/module.h>
#include<linux/init.h>
//#include <rtai_fifos.h>
#include "3718.h"
#include "3712.h"
//Arcom22//Arcom12//Arcom21//Arcom7:problems with angle
#define POSITION0 8.81//7.263//9.03//7.73
#define POSITION90 -7.97//-9.534//-8.06//-8.52
#define ORIGIN 0.38//-1.07//0.447//-0.655
#define ANGLE_15 -3.795//-4.36// -3.63//-4.49
#define ANGLE15 4.0//3.225//3.7//-1.307
#define ANGLE0 -0.167//-0.48//0.004//
#define ANGLE_WIDTH 30.0
#define POSITION_WIDTH 90.5
void   init_control2(float pposition0,float pposition90,float porigin, float pangle_15, float pangle15, float pangle0);
float commande2(float position, float angle);
float conversionVoltToAngle2(float angle);
float conversionVoltToPosition2(float position);
float commandeVoltage2(float angle, float position);


#endif
