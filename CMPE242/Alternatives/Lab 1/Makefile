ifndef DESTDIR
DESTDIR			   ?= /tmp/FriendlyARM/mini6410/rootfs
endif

CFLAGS				= -Wall -O2 -I. -lm
CC					= arm-none-linux-gnueabi-gcc
INSTALL				= install

TARGET				= combined
OBJS = lsm303_sensor.o mainfunct.o pwm_test.o
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<
	
install: $(TARGET)
	$(INSTALL) $^ $(DESTDIR)/usr/bin

clean distclean:
	rm -rf *.o $(TARGET)


.PHONY: $(PHONY) install clean distclean

