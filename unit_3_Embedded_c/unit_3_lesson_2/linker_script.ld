ENTRY(reset)

MEMORY
{
   Mem (rwx) : ORIGIN = 0x00000000, LENGTH = 128M 

}

SECTIONS 
{
   . = 0x10000;
   .reset . :
{    
    startup.o(.text)
}> Mem
 .text :
{
  *(.text)
}> Mem
.data :
{
   *(.data)
}> Mem
.bss :
{
  *(.bss)  *(COMMON)
}> Mem
.rodata :
{
*(.rodata)
}> Mem
 . = . + 0x10000;
 Stack_top = .;
}