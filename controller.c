#include "controller.h"

MODULE_LICENSE("GPL");

double x1;
double x2;
double x3;
double x4;

double position0;
double position90;
double angle_15;
double angle15;


double pasPosition;
double pasAngle;
double origin;
double angle0;

int output_fd;    /* Input and output file descriptors */
ssize_t  ret_out;    /* Number of bytes returned by read() and write() */
char buffer[100];      /* Character buffer */

void init_control(double pposition0,double pposition90,double porigin, double pangle_15, double pangle15, double pangle0){

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



double commande(double angle, double position){

	double x1k;
	double x2k;
	double x3k;
	double x4k;
	double commande;

	
	x1k=x1;
	x2k=x2;
	x3k=x3;
	x4k=x4;

	x1=0.7143*x1k+0.0245*x2k-0.0008*x3k+0.0086*x4k+0.2815*angle-0.0251*position;
	x2=0.0239*x1k+0.8609*x2k+0.0107*x3k+0.0012*x4k-0.0199*angle+0.1396*position;
	x3=0.9140*x1k-0.3043*x2k+1.1306*x3k+0.2351*x4k-0.1149*angle+0.4000*position;
	x4=-2.4476*x1k+0.0016*x2k-0.1546*x3k+0.7222*x4k+1.6173*angle-0.1150*position;

	commande= -(-80.3092*x1-9.6237*x2-14.1215*x3-23.6260*x4);	

  /*
     ret_out = write (output_fd, &buffer, (ssize_t) ret_in);
            if(ret_out != ret_in){
                ///Write error 
                perror("write");
                return 4;
            }*/
    return commande;
   

}


double conversionVoltToAngle(double angle){
		
		double angle_converti=0;
		angle_converti= (angle-angle0)/pasAngle*3.14/180.0;
		printk("angle_converti = %d radians\n",(int)(angle_converti*1000));
		return angle_converti;
}

double conversionVoltToPosition(double position){
	
	double position_converti=0;
	position_converti = (position-origin)/pasPosition/100.0;
	printk("position_converti = %d mm\n",(int)(position_converti*1000));
	return position_converti;
}

double commandeVoltage(double angle, double position){
return commande(conversionVoltToAngle(angle),conversionVoltToPosition(position));
}


static int init_controller(void) {
  output_fd = open("bigbrother.txt", O_CREAT, 0644);
    if(output_fd == -1){
        printk("[ERROR] Impossible to open bigbrother.txt\n");
        }
  init_control(POSITION0,POSITION90, ORIGIN, ANGLE_15,ANGLE15,ANGLE0);
  return 0;
}



static void exit_controller(void) {
 close (output_fd);
}

module_init(init_controller);
module_exit(exit_controller);

EXPORT_SYMBOL(init_control);
EXPORT_SYMBOL(commande);
EXPORT_SYMBOL(conversionVoltToAngle);
EXPORT_SYMBOL(conversionVoltToPosition);
EXPORT_SYMBOL(commandeVoltage);

