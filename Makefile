obj-m	   := 3718.o 3712.o SJA1000.o controller.o sensor.o pendule1.o pendule2.o

PATH := /opt/x86_64/gcc/gcc-3.4.4/bin:$(PATH)
KIT1 = arcom12.esiee.fr
KIT2 = arcom22.esiee.fr
CURRENT = 2.6.16.14-arcom1
KDIR = /usr/lib/arcom/lib/modules/${CURRENT}/build
PWD = $(shell pwd)
EXTRA_CFLAGS += -I/usr/lib/arcom/realtime/include -Wall -ffast-math -mhard-float
default:
	@echo --------------------------------------
	@echo PWD = $(PWD)
	@echo CURRENT = $(CURRENT)
	@echo KDIR = $(KDIR)
	i386 -B --uname-2.6 make -C $(KDIR) M=$(PWD) modules

clean:
	-rm -f *.o *.ko .*.cmd .*.flags *.mod.c *~
	-rm -r .tmp*
send1:
	scp *.ko runarcom arcom@$(KIT1):/home/arcom
	ssh arcom@$(KIT1)
send2:
	scp *.ko runarcom arcom@$(KIT2):/home/arcom
	ssh arcom@$(KIT2)

