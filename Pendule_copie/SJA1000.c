#include "SJA1000.h"


void send(int id, int dlc, void* adress){
   	int i=0;
    u8 message[8];
    u8 idt1, idt2,lecture;
	lecture=inb(STATUS_SJA);
	
	if(((lecture&0x04)==0x04)&&id<4096&&dlc<9){
		idt2=id&0x003;
		idt2=idt2<<5;
		idt2=idt2|dlc;
		idt1=id>>3;
		//printk("IDT1%8x\n",idt1);
		//printk("IDT2%8x\n",idt2);
		outb(idt1,IDT1);
		outb(idt2,IDT2);
		memcpy(&message,adress,dlc) ;
		
		while(i<dlc){
			 outb(message[i],DATAT+i);
			 i++;
		}
			 
	   outb(0x01,COMMAND);
	
	}
	

}

void receive(void* adress, int* id,int* dlc){
    u8 idt1,idt2,lecture;
	u8 message[8];
	int i=0;
	lecture=inb(INTERRUPT);
	printk("INTTERUPT=%d\n",lecture);
    lecture=inb(STATUS_SJA);
    printk("Condition=%d\n",lecture&0x01);
	if((lecture&0x01)==0x01){
		idt1=inb(IDR1);
		idt2=inb(IDR2);
		//printk("idt2=%8x\n",idt2);
		//printk("idt1=%8x\n",idt1);
		*dlc=(int)idt2&0x0F;
		*id=(int)idt1;
		*id=*id<<3;
		*id = *id |(int)(idt2>>5);

		
		if(*dlc>0){
			while(i<*dlc){
			message[i]=inb(DATAR+i);
			//printk("message=%8x\n",message[i]);
			i++;
			}
		outb(0x04,COMMAND);
		memcpy(adress,&message,*dlc) ;
		
	    }
	}
	

	
}



/********************************************************/
/*   Initialisation du/des SJA1000                      */
/********************************************************/
void init_SJA1000(void) 
{
	
    outb(0x03,CONTROL);
	outb(0xFF,ACR);
	outb(0xFF,AMR);
	outb(0x03,BTR0);
	outb(0x1C,BTR1);
	outb(0xFA,OCR);
	outb(0x02,CONTROL);
  	
}





int SJA1000init(void) {

   init_SJA1000();
 
 return(0);
 
}


void SJA1000exit(void) {

}



module_init(SJA1000init);
module_exit(SJA1000exit);

EXPORT_SYMBOL(receive);
EXPORT_SYMBOL(send);


