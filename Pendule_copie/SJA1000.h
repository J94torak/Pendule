#ifndef __SJA1000__
#define __SJA1000__

#include<linux/init.h>
#include<linux/module.h>

#include <asm/io.h>
#include <asm/irq.h>
#include <rtai.h>
#include <rtai_sched.h>
#include <rtai_fifos.h>


MODULE_LICENSE("GPL");


/* define pour gestion registres CAN 7841*/

#define CONTROL 0x180
#define COMMAND (CONTROL + 1)
#define STATUS_SJA (CONTROL + 2)
#define INTERRUPT (CONTROL + 3)
#define ACR (CONTROL + 4) //ACCEPTANCE CODE REGISTER
#define AMR (CONTROL + 5)// ACCEPTANCE MASK REGISTER
#define BTR0 ( CONTROL + 6)//BUS TIMER REGISTER 0 
#define BTR1 ( CONTROL + 7)//BUS TIMER REGISTER 1 
#define OCR ( CONTROL + 8 )//OUTPUT CONTROL REGISTER 
#define TESTR ( CONTROL + 9)
#define IDT1 (CONTROL + 10)
#define IDT2 (CONTROL +11)
#define DATAT (CONTROL + 12) //PREMIER @ jusqu'à 19
#define IDR1 (CONTROL + 20) 
#define IDR2 (CONTROL + 21)
#define DATAR (CONTROL + 22)//PREMIER @ jusqu'à 30
#define CLOCK_DEVIDER (CONTROL + 31)

void send(int id, int dlc, void* adress );
void receive(void* adress, int* id,int* dlc);

#endif
