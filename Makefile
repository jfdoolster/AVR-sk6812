src=main
avrType=atmega324pa
avrFreq=16000000

progDev=usb
progType=dragon_jtag

#cflags=-g -DG_CPU=$(avrFreq) -Wall -Os -Werror -Wextra
cflags=-Wall -Os
aflags=-I /usr/share/asm/

edit:
	gvim -v Makefile

connect:
	avrdude -p$(avrType) -c$(progType) -P$(progDev) -n

erase:
	avrdude -p$(avrType) -c$(progType) -P$(progDev) -e

fuse:
	avrdude -p$(avrType) -c$(progType) -P$(progDev) -U lfuse:w:0xff:m
	#avrdude -p$(avrType) -c$(progType) -P$(progDev) -U lfuse:w:0x62:m

compile:
	avr-gcc $(cflags) -mmcu=$(avrType) -c -o $(src).o $(src).c
	avr-gcc $(cflags) -mmcu=$(avrType) -o $(src).elf $(src).o
	avr-objcopy -j .text -j .data -O ihex $(src).elf $(src).hex
	rm -f $(src).o $(src).elf

flash:
	avrdude -p$(avrType) -c$(progType) -P$(progDev)-v -e -U flash:w:$(src).hex

clean:
	rm -f $(src).hex
