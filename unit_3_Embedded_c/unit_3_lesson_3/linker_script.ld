/* linker_scirpt -> cortex-m3
Eng. : Ahmed Nabil 
*/ 


MEMORY
{
 FLASH	(rx)		: ORIGIN = 0X08000000,  LENGTH = 128k
 SRAM		(rwx)		: ORIGIN = 0X20000000,  LENGTH = 20K
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
        stack_top = . + 0x2000 ;

            }> SRAM


}