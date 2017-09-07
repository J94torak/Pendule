#ifndef __3718__
#define __3718__

#include<asm/io.h>

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
#define RANGE_2_5 1
#define RANGE_1_25 2
#define RANGE_0_625 3
#define RANGE_0__10 4
#define RANGE_0__5 5
#define RANGE_0__2_5 6
#define RANGE_0__1_25 7
#define RANGE_10 8

int init3718(void);
void SetChanel(unsigned int);
void ADRangeSelect(unsigned int,unsigned int);
u16 ReadAD(void);


#endif
