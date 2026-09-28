/**
 * @file        arch/riscv32/esp32c3/src/esp-hal/esp_startup.S
 * @brief       Minimal CRT0 for ESP32-C3 (M-mode, single hart)
 *
 * Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

  .section .text.entry, "ax"
  .global _start
  .type _start, @function
_start:
  /* Disable interrupts during bring-up. */
  csrci mstatus, 8

  /* Set stack pointer. */
  la sp, _stack_top

  /* Clear BSS. */
  la a0, _sbss
  la a1, _ebss
1:
  bgeu a0, a1, 2f
  sw zero, 0(a0)
  addi a0, a0, 4
  j 1b
2:

  /* Copy .data from load address if needed (LMA != VMA). */
  la a0, _sdata
  la a1, _edata
  la a2, _sidata
  beq a0, a2, 4f
3:
  bgeu a0, a1, 4f
  lw t0, 0(a2)
  sw t0, 0(a0)
  addi a0, a0, 4
  addi a2, a2, 4
  j 3b
4:

  /* Point exceptions/interrupts at FreeRTOS trap handler (not ROM). */
  la t0, freertos_risc_v_trap_handler
  csrw mtvec, t0

  call main

5:
  j 5b

  .size _start, . - _start
