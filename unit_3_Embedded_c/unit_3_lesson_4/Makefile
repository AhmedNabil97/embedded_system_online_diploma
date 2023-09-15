CC=arm-none-eabi-
CFLAGS= -mcpu=cortex-m4 -mthumb -gdwarf-2 -g
INCS=-I .
LIBS= 
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
AS=$(wildcard *.s)
ASOBJ=$(AS:.s=.o)
project_name=unit3-lesson4-cortex-m4

all: $(project_name).bin
	@echo "project is succesfully build"



%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS)  $< -o $@



$(project_name).elf: $(OBJ) $(ASOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(ASOBJ) -o $@ -Map=Map_file.map
	cp $(project_name).elf $(project_name).axf 

$(project_name).bin: $(project_name).elf 
	$(CC)objcopy.exe -O binary $< $@
	

clean_all:  
	rm *.elf *.bin *.o

clean:
	rm *.elf *.bin