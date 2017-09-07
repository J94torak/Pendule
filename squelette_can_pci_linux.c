/***********************************************************************/
/* squelette gestion pci carte CAN 7841                                                    */
/* sous rtai                                                           */
/*                                                                     */
/***********************************************************************/

#include<linux/module.h>
#include<linux/version.h>
#include <asm/io.h>
#include <linux/pci.h>
#include <asm/irq.h>
#include <rtai.h>
#include <rtai_sched.h>



MODULE_LICENSE("GPL");



/* define pour gestion PCI CARTE CAN 7841 */
#define CAN_VENDOR_ID 0x144A
#define CAN_DEVICE_ID 0x7841



/* déclaration variables pour addresse et irq */
/*  de la carte CAN PCI 7841                  */
static u32 base;  //adresse de base de la carte CAN
static u32 base2;
static unsigned int irq_7841;



/*******************************************************/
/* initialisation de la carte CAN                      */
/*     - recherche de l'adresse et de l'irq sur le PCI */
/*     - initialisation du SJA1000 : a completer       */
/******************************************************/
void init_can(void)
{
  /* initialisation PCI */
   u16 vendor,device;   
  u8 revision;
 struct pci_dev *dev=NULL;
 
  // RECHERCHE DE L'ADRESSE DE LA CARTE SUR LE BUS PCI

 if(pci_present())
    {
      dev = pci_find_device(CAN_VENDOR_ID, CAN_DEVICE_ID,dev);
      pci_read_config_dword(dev,PCI_BASE_ADDRESS_2,&base);
      if(dev==NULL) 
	{
	  printk("cannot init PCI 7841 card\n");
	  return -1;
	}
    } 
  else 
    {
      printk("cannot init PCI 7841 card\n");
      return -1 ;
    }
  
  base &= PCI_BASE_ADDRESS_IO_MASK; //adresse de base du 1er SJA1000
  printk("CARTE 7841 : BASE  0x%4x\n",base);
  base2 =  base + 0x80;   //adresse de base du 2eme SJA1000
  
  irq_7841 = dev->irq;  //on récupère l'irq de la carte CAN
  
  printk("CARTE 7841 Irq: %d\n", irq_7841);
  pci_read_config_byte(dev,PCI_REVISION_ID,&revision);
  printk("CARTE 7841 Revision : %u\n", revision);
  pci_read_config_word(dev,PCI_VENDOR_ID,&vendor);
  printk("CARTE 7841, VendorId : %x\n", vendor);
  pci_read_config_word(dev,PCI_DEVICE_ID,&device);
  printk("CARTE 7841 DeviceId : %x\n", device);
  printk("CARTE 7841 Base : %x\n", base);
  
  /**** initialisation SJA 1000 ****/
  /* a completer */
}




int init_module(void) {

  int ierr;

  init_can(); 

 
 return(0);
}

void cleanup_module(void) {
 
}

