#include<linux/init.h>
#include<linux/module.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <rtai.h>
#include <rtai_sched.h>
#include"3718.h"
#include"3712.h"
#include "controller2.h"
#include "sensor.h"
#include "SJA1000.h"


MODULE_LICENSE("GPL");

#define ID 2
/* define pour tache periodique */
#define STACK_SIZE  2000
#define TICK_PERIOD 1000000    //  1 ms
#define PERIODE_CONTROL  10000000 //20ms
#define PERIODE_CONTROL2 10000000 //5ms
#define N_BOUCLE 10000000
#define NUMERO1 1
#define NUMERO2 2
#define NUMERO3 3
#define NUMERO4 4
#define PRIORITE1 1
#define PRIORITE2 2
#define PRIORITE3 3
#define PRIORITE4 4


#define SYNCHRONE   1 // 1 synchrone 0 asyncrone

#define IRQ 5

/* RT_TASK */
//static RT_TASK calibration;
static RT_TASK acquisition;
static RT_TASK control;
static RT_TASK actuator;

u16 angle_pendule1;
u16 position_pendule1;
u16 commande_pendule1;

u16 angle_pendule2;
u16 position_pendule2;
u16 commande_pendule2;



RTIME now;

u16 valeur=0;


void control_pendule2(long arg){
u16 commande_pendule2l=0;
while(1){
commande_pendule2=(u16) VoltageToValue(commandeVoltage2(valueToVoltagePolar(5,angle_pendule2),valueToVoltagePolar(10,position_pendule2)));
commande_pendule2l=commande_pendule2;
//printk("commande pendule 2 envoyé: %d\n",(int)commande_pendule2l );
send(0x22,2,&commande_pendule2l);
//printk("commande pendule 2 envoyé: %d\n",(int)commande_pendule2 );

rt_task_suspend(&control);
}
}

void acquisition_pendule1(long arg){
u16 envoie[2];
while(1){
angle_pendule1 = acquisition_angle();
position_pendule1 = acquisition_position();
envoie[0] = angle_pendule1;
envoie[1] = position_pendule1;

	send(0x10,4,&envoie);
	printk("angule pendule 1 envoyé: %d\n",(int)(1000.0*valueToVoltagePolar(5,(int)angle_pendule1)) );
	printk("position pendule 1 envoyé: %d\n",(int)(1000.0*valueToVoltagePolar(10,(int)position_pendule1)) );
	rt_task_wait_period();
}
}

void actuator_pendule1(long arg){
RTIME nowp;
while(1){

float commande=valueToVoltagePolar(10, (int)commande_pendule1);
//printk("Commande = %dmv\n", (int)(commande*1000.0));
SetDAVol(0,0.52*commande);
/*SetDA(0,commande_pendule1);
printk("Commande_Value=%d\n",commande_pendule1);*/
rt_task_suspend (&actuator);
}

}

void test4(void){
	
	u16 adress[2];
    int id=0;
    int dlc=0;
    u16 now;
	//int status;
	//int status=0;

	receive(&adress, &id,&dlc);
	////printk("id=%d\n",id);
	////printk("dlc=%d\n",dlc);
	////printk("valeur recue = %d\n",adress[0]);

	if(id==0x12 && dlc==2){
        commande_pendule1=adress[0];
        	
        //printk("commande adress 0 = %d\n",commande_pendule1);
        rt_task_resume(&actuator);//rtask_resume actuator
		  
    }
    if(id==0x20 && dlc==4){
        angle_pendule2=adress[0];
         //printk("angle recue = %d mv\n",(int)(1000.0*valueToVoltagePolar(5,(int)adress[0])));
        position_pendule2=adress[1];
              //printk("pos recue = %d mv\n",(int)(1000.0*valueToVoltagePolar(10,(int)adress[1])));
        rt_task_resume(&control);//rtask_resume control
 	}
	
	rt_ack_irq(IRQ);/* acquittement de l'interruption */	
	

}



static int pendule1_init(void) {

  int ierr_1,ierr_2,ierr_3,ierr_4;




 
	 /*mode interruption*/
	rt_global_cli(); /* desactivation des IT */
	rt_request_global_irq(IRQ,test4); /*installation du handler */                                           /* sur l'IT num_irq       */
	rt_startup_irq(IRQ); /* activation de la ligne d'interruption */
	rt_global_sti(); /* re-activation des IT */
	

    /* creation tache périodiques*/
  
 rt_set_oneshot_mode();
  ierr_1 = rt_task_init(&acquisition,acquisition_pendule1,0,STACK_SIZE, PRIORITE2, 0, 0);
  ierr_3 = rt_task_init(&control,control_pendule2,0,STACK_SIZE, PRIORITE3, 1, 0);
  ierr_4 = rt_task_init(&actuator,actuator_pendule1,0,STACK_SIZE, PRIORITE4, 1, 0);
  



  start_rt_timer(nano2count(TICK_PERIOD));
  now = rt_get_time();
	
	
  rt_task_make_periodic(&acquisition, now , nano2count(PERIODE_CONTROL));
 

	
 
 
 return(0);
}

static void pendule1_exit(void) {

/*desactive mode interruption*/
	rt_shutdown_irq(IRQ);/* désactivation de l'IT num_irq */
	rt_free_global_irq(IRQ); /* désintallation du handler */


  stop_rt_timer(); 
 rt_task_delete(&acquisition);
 rt_task_delete(&control);
rt_task_delete(&actuator);

}



module_init(pendule1_init);
module_exit(pendule1_exit);
