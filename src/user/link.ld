/*
*  linker for user programs
*  since we do not utilize higher half kernel approach
*  our programs load at 1G
*/
OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
SECTIONS
 {
   . = 0x40000000;
   .text : { *(.text) }
   .data : { *(.data) }
   .bss  : { *(.bss)  }
 }