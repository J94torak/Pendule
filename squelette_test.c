
#include<linux/init.h>
#include<linux/module.h>

#include <asm/io.h>
#include <asm/irq.h>
#include <rtai.h>
#include <rtai_sched.h>
#include <rtai_fifos.h>

#include"3718.h"



MODULE_LICENSE("GPL");

/* define pour tache periodique */
#define STACK_SIZE  2000
#define TICK_PERIOD 1000000    //  1 ms
#define PERIODE_CONTROL 20000000 //20ms
#define N_BOUCLE 10000000
#define NUMERO 1
#define PRIORITE 1

/* RT_TASK */
static RT_TASK tache_horloge;

/* tache generation dent de scie */
void test(long arg) {

  u16 i=0;
   while (1) 
   {
    i=ReadAD();
    //i=(i>>12)-1;
    printk("Voltage=%d\n",(int)i);
    rt_task_wait_period();
 }
}


static int test_init(void) {

  int ierr;
  RTIME now;


    /* creation tache périodiques*/
   if(SetChanel(0x01)!=0x00)
      printk("SetChannel=0x01");
  else
      printk("No answer");
    ADRangeSelect(0x01,RANGE_0__10);
  rt_set_oneshot_mode();
   ierr = rt_task_init(&tache_horloge,test,0,STACK_SIZE, PRIORITE, 0, 0);  
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
