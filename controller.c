#include "controller.h"

double x1;
double x2;
double x3;
double x4;

double position0;
double position85;
double angle_15;
double angle15;

double pasPosition;
double pasAngle;

void init_control(double pposition0,double pposition85, double pangle_15, double pangle15){

 	x1=0;
 	x2=0;
 	x3=0;
 	x4=0;
	position0=pposition0;
	position85=pposition85;
	angle_15=pangle_15;
	angle15=pangle15;
	pasPosition=(position0-position85)/85.0 ;   //Volt/cm
  pasAngle= (angle_15-angle15)/30.0;          //volt/degre


}



double commande(double angle, double position){

	double x1k;
	double x2k;
	double x3k;
	double x4k;
	

	
	x1k=x1;
	x2k=x2;
	x3k=x3;
	x4k=x4;

	x1= 0.6300*x1k-0.1206*x2k-0.0008*x3k+0.0086*x4k+0.3658*angle+0.1200*position;
	x2=-0.0953*x1k+0.6935*x2k+0.0107*x3k+0.0012*x4k+0.0993*angle+0.3070*position;
	x3=-0.2896*x1k-1.9184*x2k+1.1306*x3k+0.2351*x4k+1.0887*angle+2.0141*position;
	x4=-3.9680*x1k-1.7733*x2k-0.1546*x3k+0.7222*x4k+3.1377*angle+1.6599*position;

	return -80.3092*x1-9.6237*x2-14.1215*x3-23.6260*x4;	

}


double conversionVoltToAngle(double angle){
		
		double angle_converti=0;
		angle_converti= -angle/pasAngle*3.14/180.0;
		printk("angle_converti = %d radians\n",(int)(angle_converti*1000));
		return angle_converti;
}

double conversionVoltToPosition(double position){
	
	double position_converti=0;
	position_converti = position/pasPosition/100.0;
	printk("position_converti = %d cm\n",(int)(position_converti*100));
	return position_converti;
}

double commandeVoltage(double angle, double position){
return commande(conversionVoltToAngle(angle),conversionVoltToPosition(position));
}


static int init_controller(void) {

	init_control(9.53,-7.41,-3.87,4.037);
  return 0;
}



static void exit_controller(void) {
}


module_init(init_controller);
module_exit(exit_controller);

EXPORT_SYMBOL(init_control);
EXPORT_SYMBOL(commande);
EXPORT_SYMBOL(conversionVoltToAngle);
EXPORT_SYMBOL(conversionVoltToPosition);
EXPORT_SYMBOL(commandeVoltage);

