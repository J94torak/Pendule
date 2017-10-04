/*******************************************************************/
/* Fichier entete pour utilisation carte advantech PCM-3712 PC-104 */
/* version : 1.0                                                   */
/* auteurs : RK                                                    */
/*******************************************************************/

#ifndef __3712__
#define __3712__

#include<asm/io.h>
#include <asm/irq.h>
#include<linux/module.h>
#include<linux/init.h>

#define BASE_3712 0x300
#define PCM3712_DA0 BASE_3712
#define PCM3712_DA1 (BASE_3712 +2)
#define PCM3712_SYNC (BASE_3712 +4)
#define PCM3712_OUT (BASE_3712 +5)


int init3712(void);
void SetDA(unsigned char channel,int value);
int SetDAVol(unsigned char channel,float voltage);
int VoltageToValue(float voltage);

#endif









