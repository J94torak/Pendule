#ifndef __CONTROLLER__
#define __CONTROLLER__
#include<asm/io.h>
#include <asm/irq.h>
#include<linux/module.h>
#include<linux/init.h>
#include <rtai_fifos.h>
#include "3718.h"
#include "3712.h"
//Arcom12//Arcom22//Arcom21//Arcom7:problems with angle
#define POSITION0 8.19//8.09////9.03//7.73
#define POSITION90 -8.626///-8.70///-8.06//-8.52
#define ORIGIN 0.4686//-0.57////0.447//-0.655
#define ANGLE_15 -4.379//-3.78//// -3.63//-4.49
#define ANGLE15 3.314//4.0////3.7//-1.307
#define ANGLE0 -0.44//-0.124////0.004//
#define ANGLE_WIDTH 30.0
#define POSITION_WIDTH 90.5
void   init_control1(float pposition0,float pposition90,float porigin, float pangle_15, float pangle15, float pangle0);
float commande1(float position, float angle);
float conversionVoltToAngle1(float angle);
float conversionVoltToPosition1(float position);
float commandeVoltage1(float angle, float position);




#endif
