/* linker_scirpt -> ARM cortex-m3
Eng. : Ahmed Nabil 
*/ 

MEMORY
{
  FLASH (rx) : ORIGIN = 0X08000000 , LENGTH = 64K
  SRAM  (rwx) : ORIGIN = 0X20000000 , LENGTH = 20K
}

SECTIONS
{

  .text :
{

   *(.vector)
   *(.text)
    . = ALIGN(4) ;
     *(.rodata)
    . = ALIGN(4) ;
    E_text = . ;

}> FLASH


.data : 
{

    S_data = . ;
    *(.data)
    . = ALIGN(4) ;
    E_data = . ;

}> SRAM AT> FLASH

.bss :
  { 
     S_bss = . ;
     *(.bss)
     . = ALIGN(4) ;
     *(.common)
     . = ALIGN(4) ;
     E_bss = . ;
   
  }    
  . = . + 0x2000 ;
  Stack_top = . ;
}