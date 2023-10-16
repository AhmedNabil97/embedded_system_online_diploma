CC=arm-none-eabi-
CFLAGS=-mcpu=cortex-m3 -mthumb -gdwarf-2
INCS=-I .
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
project_name=Pressure_Detection

all: $(project_name).bin
	@echo --build is done--

%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@

$(project_name).elf: $(OBJ)
	$(CC)ld.exe -T linker_script.ld $(OBJ) -o $@ -Map=Map_file.map

$(project_name).bin: $(project_name).elf
	$(CC)objcopy.exe -O binary $< $@



clean: 
	rm *.elf *.bin
clean_all:
	rm *.o *.elf *.bin *.hex *.asm