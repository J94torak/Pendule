obj-m	   := 3718.o 3712.o  sensor.o controller.o  squelette_test.o

PATH := /opt/x86_64/gcc/gcc-3.4.4/bin:$(PATH)
KIT = arcom20.esiee.fr
CURRENT = 2.6.16.14-arcom1
KDIR = /usr/lib/arcom/lib/modules/${CURRENT}/build
PWD = $(shell pwd)
EXTRA_CFLAGS += -I/usr/lib/arcom/realtime/include -Wall -ffast-math -mhard-float
default:
	@echo --------------------------------------
	@echo PWD = $(PWD)
	@echo CURRENT = $(CURRENT)
	@echo KDIR = $(KDIR)
	/opt/x86.64/gcc/gcc-3.4.4/bin|gcc -m32 -march=i386 bigbrother.c -o bigbrother
	i386 -B --uname-2.6 make -C $(KDIR) M=$(PWD) modules

clean:
	-rm -f *.o *.ko .*.cmd .*.flags *.mod.c *~
	-rm -r .tmp*
send:
	scp *.ko runarcom bigbrother arcom@$(KIT):/home/arcom
	ssh arcom@$(KIT)

send3: 
	scp *.ko runarcom arcom@arcom3.esiee.fr:/home/arcom
	ssh arcom@arcom3.esiee.fr

send20:
	scp *.ko runarcom arcom@arcom20.esiee.fr:/home/arcom
	ssh arcom@arcom20.esiee.fr
send12:
	scp *.ko runarcom arcom@arcom12.esiee.fr:/home/arcom
	ssh arcom@arcom12.esiee.fr
send22:
	scp *.ko runarcom arcom@arcom22.esiee.fr:/home/arcom
	ssh arcom@arcom22.esiee.fr

send7:
	scp *.ko runarcom arcom@arcom7.esiee.fr:/home/arcom
	ssh arcom@arcom7.esiee.fr
send21:
	scp *.ko runarcom arcom@arcom21.esiee.fr:/home/arcom
	ssh arcom@arcom21.esiee.fr

