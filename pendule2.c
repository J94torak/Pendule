
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
#define PERIODE_CONTROL2 5000000 //5ms
#define N_BOUCLE 10000000
#define NUMERO1 1
#define NUMERO2 2
#define NUMERO3 3
#define NUMERO4 4
#define PRIORITE1 1
#define PRIORITE2 2
#define PRIORITE3 3
#define PRIORITE4 4

/* RT_TASK */
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

void control_pendule1(long arg){
while(1){
commande_pendule1=(u16) VoltageToValue(commande(valueToVoltagePolar(5, angle_pendule1),valueToVoltagePolar(10, position_pendule1))));
send(0x12,2,&commande_pendule1);
printk("commande pendule 1 envoyé: %d\n",(int) commande_pendule1);
rt_task_suspend (&control);
}
}

void acquisition_pendule2(long arg){
u16 envoie[2];

while(1){
envoie[0] = acquisition_angle();
envoie[1] = acquisition_position();
send(0x20,4,&envoie);
rt_task_wait_period();
}

}

void actuator_pendule2(long arg){
while(1){
//double angle=valueToVoltagePolar(5, angle_pendule2);
double position=valueToVoltagePolar(10, position_pendule2);
double commande=valueToVoltagePolar(10, commande_pendule2);
printk("Commande = %dmv\n", (int)(commande*1000.0));

		if(((int)(position*1000.0))<8000&&((int)(position*1000.0))>-5600&&((int)(commande*1000.0))>-10000&&((int)(commande*1000.0))<10000)
			SetDA(0,commande_pendule2);
		else{
			printk("Position NOK \n");
			SetDAVol(0,0.0);
			}
rt_task_suspend (&actuator);
}

}

void lecture_can(long arg){
u16 adress[2];
int id=0;
int dlc=0;
	while(1){
    receive(&adress, &id,&dlc);
    printk("id= %d\n",id);
    printk("dlc= %d\n",dlc);

    if(id==0x22 && dlc==2){
        commande_pendule2=adress[0];
        printk("commande adress 0 = %d\n",adress[0]);
        rt_task_resume(&actuator);//rtask_resume actuator
    }
    if(id==0x10 && dlc==4){
        angle_pendule1=adress[0];
        printk("angle adress 0 = %d\n",adress[0]);
        position_pendule1=adress[1];
        printk("pos adress 1 = %d\n",adress[1]);
        rt_task_resume(&control);//rtask_resume control
    }
rt_task_wait_period();
}
}



static int pendule2_init(void) {

  int ierr_1,ierr_2,ierr_3,ierr_4;
  RTIME now;


    /* creation tache périodiques*/
  //init_control(double pposition0,double pposition85, double pangle_15, double pangle15);
  rt_set_oneshot_mode();
  ierr_1 = rt_task_init(&acquisition,acquisition_pendule2,0,STACK_SIZE, PRIORITE2, 0, 0);
  ierr_2 = rt_task_init(&lecture,lecture_can,0,STACK_SIZE, PRIORITE1, 0, 0);
  ierr_3 = rt_task_init(&control,control_pendule1,0,STACK_SIZE, PRIORITE3, 1, 0);
  ierr_4 = rt_task_init(&actuator,actuator_pendule2,0,STACK_SIZE, PRIORITE4, 1, 0);



  start_rt_timer(nano2count(TICK_PERIOD));
  now = rt_get_time();
  rt_task_make_periodic(&acquisition, now, nano2count(PERIODE_CONTROL));
  rt_task_make_periodic(&lecture, now, nano2count(PERIODE_CONTROL2));

 
 
 return(0);
}

static void pendule2_exit(void) {
 stop_rt_timer(); 
 rt_task_delete(&acquisition);
rt_task_delete(&lecture);
 rt_task_delete(&control);
rt_task_delete(&actuator);
}



module_init(pendule2_init);
module_exit(pendule2_exit);

