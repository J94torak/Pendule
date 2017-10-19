
#include<linux/init.h>
#include<linux/module.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <rtai.h>
#include <rtai_sched.h>
#include <rtai_fifos.h>
#include <rtai_nam2num.h>
#include"3718.h"
#include"3712.h"
#include "controller.h"
#include "sensor.h"
#include "SJA1000.h"


MODULE_LICENSE("GPL");

/* define pour tache periodique */
#define STACK_SIZE  2000
#define TICK_PERIOD 1000    //  1 ms
#define PERIODE_CONTROL 10000000 //10ms
#define N_BOUCLE 10000000
#define NUMERO 1
#define PRIORITE 1



u16 angle_buff[2];
u16 position_buff[2];
u16 commande_buff[2];


/* RT_TASK */
static RT_TASK tache_horloge;

/* tache generation dent de scie */
void test(long arg) {

  u16 i=0;
  unsigned int f=0;
   while (1) 
   {
    i=ReadAD();
//Lecture pour 0 à 10V
    f=(unsigned int)i;
    f=f*2+f/2;
    printk("Voltage=%dmV\n",f);
    rt_task_wait_period();
 }
}




void test2(long arg){
	
	int voltage=0;
   while (1) 
   {
   if(SetChanel(0x00)!=0x00)
      printk("SetChannel=0x00\n");
  else
      printk("No answer\n");
    voltage = ReadAD();
    printk("ValueRead channel 0=%d\n",(unsigned int)voltage);
    SetDAVol(0,valueToVoltagePolar(5,(int)(voltage)));
    
      if(SetChanel(0x01)!=0x00)
      printk("SetChannel=0x01\n");
  else
      printk("No answer\n");
    voltage = ReadAD();
    printk("ValueRead channel 1=%d\n",(unsigned int)voltage);
    SetDAVol(1,valueToVoltagePolar(10,(int)(voltage)));
    
    rt_task_wait_period();
 }
 
}

void test3(long arg){

	int angle=0,position=0;
	//float commande=0;
	int now;
	int status;
	char conversion[8];
	
	while(1){
		
		angle   = (int) acquisition_angle();
		position = (int )acquisition_position();
		now=(int)rt_get_time_ns();
		printk("Temps:%d angle=%d, position%d",now,angle,position);
		
		
		num2nam( (unsigned long)now ,&conversion);	
		conversion[7]=' ';
		status = rtf_put(0,&conversion,8);
		
		
		num2nam( (unsigned long)angle,&conversion);	
		conversion[7]='\n';
		status = rtf_put(0,&conversion,8);
		
		num2nam( (unsigned long)now ,&conversion);	
		conversion[7]=' ';
		status = rtf_put(1,&conversion,8);
		
		
		num2nam( (unsigned long)position,&conversion);	
		conversion[7]='\n';
		status = rtf_put(1,&conversion,8);
		
		
		//printk("positionV=%dmv\n",(int)(positionV*1000.0)); 
		//printk("angleV=%dmv\n",(int)(angleV*1000.0)); 
		/*commande  = commandeVoltage(angle,position);
		commande_buff[0]=(u16)rt_get_time_ns();
        commande_buff[1]=commande;
        status=-1;
       	
        status = rtf_put(2,commande_buff,2); 
		
		
		
		printk("Commande = %dmv\n", (int)(commande*1000.0));*/
		//SetDAVol(0, 0.75*commande);       //arcom22 2.5*commande);//arcom12 0.75*commande);//arcom21 4*commande);
		
		
		rt_task_wait_period();
		
	}

}

static int test_init(void) {

  int ierr;
  RTIME now;


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
