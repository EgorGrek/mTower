/*
 * ESP32-C3 Super Mini linker script (Phase 1).
 * Places code/data in on-chip SRAM for load_ram / early bring-up.
 * Flash virtual addresses can be added later for XIP.
 */

OUTPUT_ARCH("riscv")
ENTRY(_start)

MEMORY
{
  iram (rx) : ORIGIN = 0x40380000, LENGTH = 0x28000
  dram (rw) : ORIGIN = 0x3FC88000, LENGTH = 0x28000
}

SECTIONS
{
  .text : ALIGN(4)
  {
    KEEP(*(.text.entry))
    *(.text .text.*)
    *(.rodata .rodata.*)
    *(.srodata .srodata.*)
    . = ALIGN(4);
    _etext = .;
  } > iram

  .data : ALIGN(4)
  {
    _sdata = .;
    *(.data .data.*)
    *(.sdata .sdata.*)
    . = ALIGN(4);
    _edata = .;
  } > dram AT> iram

  _sidata = LOADADDR(.data);

  .bss (NOLOAD) : ALIGN(4)
  {
    _sbss = .;
    *(.bss .bss.*)
    *(.sbss .sbss.*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } > dram

  .heap (NOLOAD) : ALIGN(8)
  {
    _sheap = .;
    . = . + 0x4000;
    _eheap = .;
  } > dram

  .stack (NOLOAD) : ALIGN(16)
  {
    . = . + 0x2000;
    _stack_top = .;
  } > dram

  __unprivileged_section_start__ = _etext;
  __unprivileged_section_end__ = _etext;
}
