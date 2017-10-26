
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


MODULE_LICENSE("GPL");

/* define pour tache periodique */
#define STACK_SIZE  2000
#define TICK_PERIOD 1000    //  1 ms
#define PERIODE_CONTROL 10000000 //10ms
#define N_BOUCLE 10000000
#define NUMERO 1
#define PRIORITE 1


/*
u16 angle_buff[2];
u16 position_buff[2];
u16 commande_buff[2];*/
RTIME now;

/* RT_TASK */
static RT_TASK tache_horloge;

/* tache generation dent de scie */

void test3(long arg){

	int angle=0,position=0,commande=0;
	int separateur1=-1;
	int separateur2=-32768;
	//float commande=0;
	RTIME nowp;
	//int status;
	int temps=0;
	nowp     = now;
	while(1){
		
		
		angle    = (int) acquisition_angle();
		position = (int) acquisition_position();
		//nowp     = now;
		now      = rt_get_time_ns();
		temps = (((int)now - (int)nowp )/10000);
		printk("Temps= %d angle= %d, position= %d\n",temps,angle,position);
		
		rtf_put(0,&separateur2,4);
		rtf_put(0,&temps,4);	
		rtf_put(0,&separateur1,4);
		rtf_put(0,&angle,4);	
		
						
		rtf_put(1,&separateur2,4);
		rtf_put(1,&temps,4);	
		rtf_put(1,&separateur1,4);
		rtf_put(1,&position,4);	
		
		rtf_put(2,&separateur2,4);
		rtf_put(2,&temps,4);	
		rtf_put(2,&separateur1,4);
		rtf_put(2,&commande,4);
		//SetDAVol(0, 0.75*commande);       //arcom22 2.5*commande);//arcom12 0.75*commande);//arcom21 4*commande);
		
		
		rt_task_wait_period();
		
	}

}

static int test_init(void) {

  int ierr;



    /* creation tache périodiques*/
  
  rt_set_oneshot_mode();
    
   ierr = rt_task_init(&tache_horloge,test3,0,STACK_SIZE, PRIORITE, 1, 0);  
  start_rt_timer(nano2count(TICK_PERIOD));
  now = rt_get_time();
  rt_task_make_periodic(&tache_horloge, now, nano2count(PERIODE_CONTROL));
 
 		now=rt_get_time_ns();

 
 
 return(0);
}

static void test_exit(void) {
 stop_rt_timer(); 
 rt_task_delete(&tache_horloge);

}



module_init(test_init);
module_exit(test_exit);
