/* linker_scirpt -> cortex-m4
Eng. : Ahmed Nabil 
*/ 


MEMORY
{
 FLASH	(rx)		: ORIGIN = 0X00000000,  LENGTH = 512M
 SRAM		(rwx)		: ORIGIN = 0X20000000,  LENGTH = 512M
}

SECTIONS
{
   .text : {
       *(.vector*)
       *(.text*)
       *(.rodata)
       _E_TEXT = . ;
    }> FLASH
    
    .data : {
               _S_DATA = . ;
                *(.data)  
		. = ALIGN(4) ;
		_E_DATA = . ;

             }> SRAM AT> FLASH

    .bss : {
             _S_BSS = . ;
              *(.bss)
		. = ALIGN(4) ;
              _E_BSS = . ;
            }> SRAM


}