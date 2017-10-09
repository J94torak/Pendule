#include "controller.h"

MODULE_LICENSE("GPL");

float x1;
float x2;
float x3;
float x4;

float position0;
float position90;
float angle_15;
float angle15;


float pasPosition;
float pasAngle;
float origin;
float angle0;



void init_control(float pposition0,float pposition90,float porigin, float pangle_15, float pangle15, float pangle0){

 	x1=0;
 	x2=0;
 	x3=0;
 	x4=0;
    origin=porigin;
    angle0=pangle0;
	position0=pposition0;
	position90=pposition90;
	angle_15=pangle_15;
	angle15=pangle15;
	pasPosition=(position0-position90)/POSITION_WIDTH;   //Volt/cm
    pasAngle= (angle_15-angle15)/ANGLE_WIDTH;          //volt/degre
    
}



float commande(float angle, float position){

	float x1k;
	float x2k;
	float x3k;
	float x4k;
	float commande;

	
	x1k=x1;
	x2k=x2;
	x3k=x3;
	x4k=x4;

	x1 = +0.6300*x1k +0.0261*x2k -0.0012*x3k +0.0082*x4k + 0.2703*angle - 0.0271*position;
	x2 = +0.0355*x1k +0.7967*x2k +0.0110*x3k +0.0015*x4k - 0.0303*angle + 0.2041*position;
	x3 = +1.2632*x1k -0.5989*x2k +1.1944*x3k +0.3042*x4k - 0.2209*angle + 0.7570*position;
	x4 = -2.6117*x1k -0.0831*x2k -0.2302*x3k +0.6403*x4k + 1.4933*angle - 0.1040*position;

	/*x1=0.7143*x1k+0.0245*x2k-0.0008*x3k+0.0086*x4k+0.2815*angle-0.0251*position;
	x2=0.0239*x1k+0.8609*x2k+0.0107*x3k+0.0012*x4k-0.0199*angle+0.1396*position;
	x3=0.9140*x1k-0.3043*x2k+1.1306*x3k+0.2351*x4k-0.1149*angle+0.4000*position;
	x4=-2.4476*x1k+0.0016*x2k-0.1546*x3k+0.7222*x4k+1.6173*angle-0.1150*position;*/
	
	//commande= (-80.3092*x1-9.6237*x2-14.1215*x3-23.6260*x4);
	commande= (-104.7570*x1 -15.8810*x2 -20.5358*x3 -30.5773*x4);	


    
  return commande;
   

}


float conversionVoltToAngle(float angle){
		float angle_converti=0;
		angle_converti= (angle-angle0)/pasAngle*3.14/180.0;	
		printk("angle_converti = %d radians\n",(int)(angle_converti*1000));
		return angle_converti;
}

float conversionVoltToPosition(float position){
	
	float position_converti=0;
	position_converti = (position-origin)/pasPosition/100.0;
	printk("position_converti = %d mm\n",(int)(position_converti*1000));
	return position_converti;
}

float commandeVoltage(float angle, float position){
return commande(conversionVoltToAngle(angle),conversionVoltToPosition(position));
}


static int init_controller(void) {
/*int angle_fd;  
int position_fd;
int commande_fd;
angle_fd=rtf_create(0,100);  	
position_fd=rtf_create(1,100);  
commande_fd=rtf_create(2,100);   
    if(angle_fd != 0){
        printk("[ERROR] Impossible create angle descriptor\n");
        }
            if(position_fd != 0){
        printk("[ERROR] Impossible create angle descriptor\n");
        }
            if(commande_fd != 0){
        printk("[ERROR] Impossible create angle descriptor\n");
        }*/
  init_control(POSITION0, POSITION90,ORIGIN, ANGLE_15,ANGLE15,ANGLE0);
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

