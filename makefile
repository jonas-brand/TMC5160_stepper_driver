#main directory
DIR = $(shell cd)

#program paths
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

#usb-port
USBPORT = COM3

#flags
CFLAGS = -Os -DF_CPU=16000000L -mmcu=atmega2560 -I$(DIR)\_src
BFLAGS = -D -F -V -c wiring -p ATMEGA2560 -P $(USBPORT) -b 115200

#BUILD===================================================================================================

#lists of source and object files
_src_FILES := $(shell powershell Get-ChildItem _src -Recurse -Name -Filter *.c)
OBJ_FILES := $(patsubst %.c, bin\\%.o, $(_src_FILES))

#defult rule
all: bin\\out.out

#link all .o files together
bin\\out.out: $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

#compile .c file to .o file
bin\\%.o: _src\\%.c
	powershell $$null = mkdir -Force $(dir $@)
	$(CC) $(CFLAGS) -c $^ -o $@

#BURN====================================================================================================

#convert .out to .hex, required by avrdude
bin/%.hex: bin\\%.out
	$(OBJCOPY) -O ihex -R .eeprom $^ $@

#upload code to microicontroller
burn: bin/out.hex
	$(AVRDUDE) $(BFLAGS) -U flash:w:$^

#CLEAN===================================================================================================

#delete everything in bin folder
clean:
	del $(OBJ_FILES)
	del bin\*.out bin\*.hex