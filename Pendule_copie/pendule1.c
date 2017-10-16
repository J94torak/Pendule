#include<linux/init.h>
#include<linux/module.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <rtai.h>
#include <rtai_sched.h>
#include <rtai_fifos.h>
#include <rtai_fifos.h>
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
#define PERIODE_CONTROL 10000000 //20ms
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
static RT_TASK lecture;

u16 angle_pendule1;
u16 position_pendule1;
u16 commande_pendule1;

u16 angle_pendule2;
u16 position_pendule2;
u16 commande_pendule2;


u16 origin_;
u16 position0_;
u16 position90_;
u16 angle0_;
u16 angle30_;

/*u16 angle_buff[2];
u16 position_buff[2];
u16 commande_buff[2];*/

u16 valeur=0;


void control_pendule2(long arg){
u16 commande_pendule2l=0;
while(1){
commande_pendule2=(u16) VoltageToValue(commande2(valueToVoltagePolar(5, angle_pendule2),valueToVoltagePolar(10, position_pendule2)));
commande_pendule2l=commande_pendule2;
printk("commande pendule 2 envoyé: %d\n",(int) commande_pendule2l );
send(0x22,2,&commande_pendule2l);
printk("commande pendule 2 envoyé: %d\n",(int) commande_pendule2 );

rt_task_suspend(&control);
}
}

void saw(long arg) {
  u8 lecture;
  int i=0;
  int j=0;
   while (1) 
   {
    if(i>=4096)
      i=0;
    else i=i+100;
    valeur=(u16)i;
    if(SYNCHRONE==1){
		j=0;
		do{j++;
		 lecture=inb(STATUS);}while((lecture&0x04)!=0x04&&j<20);
		 if(j<20)
		 envoyer(ID,1,&valeur);
		 printk("valeur envoyee %d\n",(int)valeur);
    }
    rt_task_wait_period();
 }
}







void acquisition_pendule1(long arg){
u16 envoie[2];
//u16 now;
//int status;
while(1){
angle_pendule1 = acquisition_angle();
position_pendule1 = acquisition_position();
envoie[0] = angle_pendule1;
envoie[1] = position_pendule1;

	send(0x10,4,&envoie);
	printk("angule pendule 1 envoyé: %d\n",(int) angle_pendule1);
	printk("position pendule 1 envoyé: %d\n",(int) position_pendule1);
	/*now=(u16)rt_get_time_ns();
	angle_buff[0] = now;
	angle_buff[1] = angle_pendule1;
	position_buff[0] = now;
	position_buff[1] = position_pendule1;
 	status=-1;
	do{
		status = rtf_put(0,angle_buff,2);
	}while(status!=2);
	status=-1;
	do{
		status = rtf_put(1,position_buff,2);
	}while(status!=2);*/
	
rt_task_wait_period();
}
}

void actuator_pendule1(long arg){
while(1){

float commande=valueToVoltagePolar(10, commande_pendule1);
printk("Commande = %dmv\n", (int)(commande*1000.0));
SetDAVol(0,0.75*commande);
	
rt_task_suspend (&actuator);
}

}

void lecture_can(long arg){

    u16 adress[2];
    int id=0;
    int dlc=0;
    u8 lecture;
	//int task_status=0;
    //int status=-1;
while(1){
    receive(&adress, &id,&dlc);
    lecture=inb(INTERRUPT);
    printk("id= %d\n",id);
    printk("dlc= %d\n",dlc);
 		
    if(id==0x12 && dlc==2){
        commande_pendule1=adress[0];
        /*commande_buff[0]=(u16)rt_get_time_ns();
        commande_buff[1]=commande_pendule1;
        status=-1;
       do{
        	status = rtf_put(2,commande_buff,2); 
			}while (status!=2);
			*/
        printk("commande adress 0 = %d\n",commande_pendule1);
        rt_task_resume(&actuator);//rtask_resume actuator
		  
    }
    if(id==0x20 && dlc==4){
        angle_pendule2=adress[0];
        printk("angle adress 0 = %d\n",adress[0]);
        position_pendule2=adress[1];
        printk("pos adress 1 = %d\n",adress[1]);
        rt_task_resume(&control);//rtask_resume control
 		 
    }
rt_task_wait_period();

}

}


void test4(void){
	
	u16 adress[2];
    int id=0;
    int dlc=0;
	//int task_status=0;
	u8 lecture;
	
	receive(&adress, &id,&dlc);
	lecture=inb(INTERRUPT);
	printk("id=%d\n",id);
	printk("dlc=%d\n",dlc);
	printk("valeur recue = %d\n",adress[0]);
	if(id==0x12 && dlc==2){
        commande_pendule1=adress[0];
        /*commande_buff[0]=(u16)rt_get_time_ns();
        commande_buff[1]=commande_pendule1;
        status=-1;
       do{
        	status = rtf_put(2,commande_buff,2); 
			}while (status!=2);
			*/
        printk("commande adress 0 = %d\n",commande_pendule1);
        //rt_task_resume(&actuator);//rtask_resume actuator
		  
    }
    if(id==0x20 && dlc==4){
        angle_pendule2=adress[0];
        printk("angle adress 0 = %d\n",adress[0]);
        position_pendule2=adress[1];
        printk("pos adress 1 = %d\n",adress[1]);
        //rt_task_resume(&control);//rtask_resume control
 	}
	
	
	rt_ack_irq(IRQ);/* acquittement de l'interruption */

}




static int test_init(void) {

  int ierr_1,ierr_2,ierr_3,ierr_4;
  RTIME now;


    /* creation tache périodiques*/
  
  rt_set_oneshot_mode();
  ierr_1 = rt_task_init(&acquisition,saw,0,STACK_SIZE, PRIORITE2, 0, 0);
  //ierr_2 = rt_task_init(&lecture,lecture_can,0,STACK_SIZE, PRIORITE1, 0, 0);
  //ierr_3 = rt_task_init(&control,control_pendule2,0,STACK_SIZE, PRIORITE3, 1, 0);
  //ierr_4 = rt_task_init(&actuator,actuator_pendule1,0,STACK_SIZE, PRIORITE4, 1, 0);
  



  start_rt_timer(nano2count(TICK_PERIOD));
  now = rt_get_time();
	
	rt_task_make_periodic(&acquisition, now +1000, nano2count(PERIODE_CONTROL));	
 // rt_task_make_periodic(&acquisition, now , nano2count(PERIODE_CONTROL));
 // rt_task_make_periodic(&lecture, now, nano2count(PERIODE_CONTROL2));
 
	
	
 
 
 return(0);
}

static void test_exit(void) {

  stop_rt_timer(); 
 rt_task_delete(&acquisition);
//rt_task_delete(&lecture);
 //rt_task_delete(&control);
//rt_task_delete(&actuator);

}



module_init(test_init);
module_exit(test_exit);
