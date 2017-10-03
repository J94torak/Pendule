
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
static RT_TASK tache_horloge;

u16 angle;   
u16 position;
u16 commande_;
u16 angle_buff[2];
u16 position_buff[2];
u16 commande_buff[2];


void test3(long arg){


	int status;
	u16 now;
	
	while(1){
		
		angle    = acquisition_angle();
		position = acquisition_position();
			
		now=(u16)rt_get_time_ns();
	    angle_buff[0] = now;
	    angle_buff[1] = angle;
	    position_buff[0] = now;
	    position_buff[1] = position;
 	    status=-1;
	    do{
	    	status = rtf_put(0,angle_buff,2);
	    }while(status!=2);
	        status=-1;
	    do{
		    status = rtf_put(1,position_buff,2);
	    }while(status!=2);
		
		
		commande_  = (u16)VoltageToValue(commande(valueToVoltagePolar(5, angle),valueToVoltagePolar(10, position)));
        commande_buff[0]=(u16)rt_get_time_ns();
        commande_buff[1]=commande_;
        status=-1;
       do{
        	status = rtf_put(2,commande_buff,2); 
			}while (status!=2);
			}

		/*
			SetDAVol(0,commande_);
		else{
			printk("Position NOK \n");
			SetDAVol(0,0.0);
			}*/
		
		rt_task_wait_period();
		
	}






static int test_init(void) {

  int ierr;
    int angle_fd;  
	int position_fd;
	int commande_fd;
	RTIME now;
	
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
        }

    /* creation tache périodiques*/
  
  rt_set_oneshot_mode();
    
   ierr = rt_task_init(&tache_horloge,test3,0,STACK_SIZE, PRIORITE, 1, 0);  
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

