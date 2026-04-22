ENTRY( _start )

__stack_size = 512;

PROVIDE( _stack_size = __stack_size );

MEMORY
{
	FLASH (rx) : ORIGIN = 0x00003000, LENGTH = 436K
	IAP (rw)  : ORIGIN = 0x20000000, LENGTH = 4
	RAM (xrw) : ORIGIN = 0x20000004, LENGTH = 32K - 4
}

PHDRS
{
	text PT_LOAD FLAGS(5);   /* R-X */
	code PT_LOAD FLAGS(5);   /* R-X */
	rptr PT_LOAD FLAGS(4);   /* R-- */
	data PT_LOAD FLAGS(6);   /* RW- */
}


SECTIONS
{
	.iapflag 0x20000000 (NOLOAD) :
	{
		KEEP(*(.iapflag*))
	} >IAP

	.init :
	{
		_sinit = .;
		. = ALIGN(4);
		KEEP(*(SORT_NONE(.init)))
		. = ALIGN(4);
		_einit = .;
	} >FLASH AT>FLASH :text
	
 /*   .vector :
    {
        *(.vector);
    } >FLASH AT>FLASH */
    
    .highcodelalign : 
    {       
        . = ALIGN(4);
        PROVIDE(_highcode_lma = .); 
    } >FLASH AT>FLASH 
    
    .highcode : 
    {
        . = ALIGN(4);
        PROVIDE(_highcode_vma_start = .);
        *(.vector);
		KEEP(*(SORT_NONE(.vector_handler)))
        *(.highcode);
        *(.highcode.*);
		. = ALIGN(4); 
        PROVIDE(_highcode_vma_end = .);
    } >RAM AT>FLASH :code

	.text :
	{
		. = ALIGN(4);
		KEEP(*(SORT_NONE(.handle_reset)))
		KEEP(*(.text.call_global_ctors)) //ccccccccc
		*(.text)
		*(.text.*)
		*(.rodata)
		*(.rodata*)
		*(.sdata2.*)
		*(.glue_7)
		*(.glue_7t)
		*(.gnu.linkonce.t.*)
		. = ALIGN(4);
	} >FLASH AT>FLASH :text

	.fini :
	{
		KEEP(*(SORT_NONE(.fini)))
		. = ALIGN(4);
	} >FLASH AT>FLASH :rptr

	PROVIDE( _etext = . );
	PROVIDE( _eitcm = . );	

	.preinit_array  :
	{
	  PROVIDE_HIDDEN (__preinit_array_start = .);
	  KEEP (*(.preinit_array))
	  PROVIDE_HIDDEN (__preinit_array_end = .);
	} >FLASH AT>FLASH :rptr
	
	.init_array     :
	{
	  PROVIDE_HIDDEN (__init_array_start = .);
	  KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
	  KEEP (*(.init_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .ctors))
	  PROVIDE_HIDDEN (__init_array_end = .);
	} >FLASH AT>FLASH :rptr
	
	.fini_array     :
	{
	  PROVIDE_HIDDEN (__fini_array_start = .);
	  KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
	  KEEP (*(.fini_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .dtors))
	  PROVIDE_HIDDEN (__fini_array_end = .);
	} >FLASH AT>FLASH :rptr
	
	.ctors          :
	{
	  /* gcc uses crtbegin.o to find the start of
	     the constructors, so we make sure it is
	     first.  Because this is a wildcard, it
	     doesn't matter if the user does not
	     actually link against crtbegin.o; the
	     linker won't look for a file to match a
	     wildcard.  The wildcard also means that it
	     doesn't matter which directory crtbegin.o
	     is in.  */
	  KEEP (*crtbegin.o(.ctors))
	  KEEP (*crtbegin?.o(.ctors))
	  /* We don't want to include the .ctor section from
	     the crtend.o file until after the sorted ctors.
	     The .ctor section from the crtend file contains the
	     end of ctors marker and it must be last */
	  KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
	  KEEP (*(SORT(.ctors.*)))
	  KEEP (*(.ctors))
	} >FLASH AT>FLASH 
	
	.dtors          :
	{
	  KEEP (*crtbegin.o(.dtors))
	  KEEP (*crtbegin?.o(.dtors))
	  KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
	  KEEP (*(SORT(.dtors.*)))
	  KEEP (*(.dtors))
	} >FLASH AT>FLASH 

	/*.dalign    : 
	{
		. = ORIGIN(RAM) + SIZEOF(.iapflag) + MAX(0x800 , SIZEOF(.highcode));
	} >RAM AT>FLASH*/

	.dlalign :
	{
		. = ALIGN(4); 
		PROVIDE(_data_lma = .);
	} >FLASH AT>FLASH

	.data :
	{
		. = ALIGN(4); 
		PROVIDE(_data_vma = .);
    	*(.gnu.linkonce.r.*)
    	*(.data .data.*)
    	*(.gnu.linkonce.d.*)
		. = ALIGN(8);
    	PROVIDE( __global_pointer$ = . + 0x800 );
    	*(.sdata .sdata.*)
    	*(.gnu.linkonce.s.*)
    	. = ALIGN(8);
    	*(.srodata.cst16)
    	*(.srodata.cst8)
    	*(.srodata.cst4)
    	*(.srodata.cst2)
    	*(.srodata .srodata.*)
    	. = ALIGN(4);
		PROVIDE( _edata = .);
	} >RAM AT>FLASH :data

	.bss (NOLOAD): 
	{
		. = ALIGN(4);
		PROVIDE( _sbss = .);
  	    *(.sbss*)
        *(.gnu.linkonce.sb.*)
		*(.bss*)
     	*(.gnu.linkonce.b.*)		
		*(COMMON*)
		. = ALIGN(4);
		PROVIDE( _ebss = .);
	} >RAM

	/DISCARD/ :
{
    *(.gcc_except_table*)
    *(.eh_frame*)
}

	PROVIDE( _end = _ebss);
	PROVIDE( end = . );
	
	.stack ORIGIN(RAM)+LENGTH(RAM) :
	{
		. = ALIGN(4);
		PROVIDE(_eusrstack = . );
	} >RAM  
}