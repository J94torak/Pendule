#ifndef __3718__
#define __3718__
#include<asm/io.h>
#include <asm/irq.h>
#include<linux/module.h>
#include<linux/init.h>


#define BASE 0x320
#define R0 BASE
#define R1 BASE  + 1
#define RANGE BASE  + 1
#define MUX BASE + 2
#define W0 BASE  + 3
#define STATUS BASE  + 8
#define CONTROLE BASE  + 9
#define COUNT_EN BASE + 10
#define W1 BASE + 11

#define RANGE_5 0
#define RANGE_0_5 1
#define RANGE_0_05 2
#define RANGE_0_005 3
#define RANGE_0__10 4
#define RANGE_0__1 5 
#define RANGE_0__0_1 6
#define RANGE_0__0_01 7
#define RANGE_10 8
#define RANGE_1 9
#define RANGE_0_1 10
#define RANGE_0_01 11

int init3718(void);
int SetChanel(unsigned char);
int ADRangeSelect(unsigned char,unsigned char);
u16 ReadAD(void);
u8 ReadChannel(void);


#endif
