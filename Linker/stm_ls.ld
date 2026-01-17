/* STM32F103C8T6
 * Flash: 64 KB @ 0x08000000
 * SRAM: 20 KB @ 0x20000000
 */

MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 64K
  RAM   (rwx): ORIGIN = 0x20000000, LENGTH = 20K
}

ENTRY(Reset_Handler)

SECTIONS
{
  /* Vector table + code + read-only data */
  .text :
  {
    KEEP(*(.isr_vector))        /* Vector table */
    *(.text*)                   /* Code */
    *(.rodata*)                 /* Read-only data */
    _etext = .;                 /* End of code */
  } > FLASH

  /* Initialized data section (load from FLASH to RAM) */
  .data : AT (LOADADDR(.text) + SIZEOF(.text))
  {
    _sdata = .;                 /* Start of .data in RAM */
    *(.data*)                   /* Initialized data */
    _edata = .;                 /* End of .data */
  } > RAM

  /* Uninitialized data (zero-init) */
  .bss :
  {
    _sbss = .;                  /* Start of .bss */
    *(.bss*)                    /* Uninitialized variables */
    *(COMMON)
    _ebss = .;                  /* End of .bss */
  } > RAM

  /* Stack pointer (grows downward) */
  ._user_stack :
  {
    . = ALIGN(8);
    _estack = ORIGIN(RAM) + LENGTH(RAM); /* Top of RAM */
  } > RAM
}

/* Symbol to copy data section from Flash */
_sidata = LOADADDR(.data);
