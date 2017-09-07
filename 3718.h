#ifndef __3718__
#define __3718__

#define BASE 0x320



int init3718(void);
void SetChanel(int);
void ADRangeSelect(int,int);
u16 ReadAD(void);


#endif
