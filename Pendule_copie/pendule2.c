
#include<linux/init.h>
#include<linux/module.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <rtai.h>
#include <rtai_sched.h>
#include <rtai_fifos.h>

#include"3718.h"
#include"3712.h"
#include "controller.h"
#include "sensor.h"
#include "SJA1000.h"


MODULE_LICENSE("GPL");

/* define pour tache periodique */
#define STACK_SIZE  2000
#define TICK_PERIOD 1000000    //  1 ms
#define PERIODE_CONTROL 10000000 //10ms
#define N_BOUCLE 10000000
#define NUMERO 1
#define PRIORITE 1

/* RT_TASK */
static RT_TASK acquisition,control,actuator;

int angle;
int position;
int commande;

void control_pendule1(long arg){



}

void acquisition_pendule2(long arg){
angle  = acquisition_angle();
		positionV = acquisition_position();


}

void actuator_pendule2(long arg){



}

void test3(long arg){

	double angleV=0,positionV=0;
	double commande=0;
	
	while(1){
		
		angleV    = acquisition_angle();
		positionV = acquisition_position();
		printk("positionV=%dmv\n",(int)(positionV*1000.0)); 
		printk("angleV=%dmv\n",(int)(angleV*1000.0)); 
		commande  = commandeVoltage(angleV,positionV);
		printk("Commande = %dmv\n", (int)(commande*1000.0));
		if(((int)(positionV*1000.0))<8000&&((int)(positionV*1000.0))>-5600&&((int)(commande*1000.0))>-10000&&((int)(commande*1000.0))<10000)
			SetDAVol(0,commande);
		else{
			printk("Position NOK \n");
			SetDAVol(0,0.0);
			}
		
		rt_task_wait_period();
		
	}

}

static int pendule2_init(void) {

  int ierr;
  RTIME now;


    /* creation tache périodiques*/
  
  rt_set_oneshot_mode();
    
   ierr = rt_task_init(&,test3,0,STACK_SIZE, PRIORITE, 1, 0);  
  start_rt_timer(nano2count(TICK_PERIOD));
  now = rt_get_time();
  rt_task_make_periodic(&tache_horloge, now, nano2count(PERIODE_CONTROL));
 

 
 
 return(0);
}

static void test_exit(void) {
 stop_rt_timer(); 
 rt_task_delete(&tache_horloge);

}



module_init(test_init);
module_exit(test_exit);

