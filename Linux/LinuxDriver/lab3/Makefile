obj-m := lab_io.o

all:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules EXTRA_CFLAGS="-g -DDEBUG"
clean:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

