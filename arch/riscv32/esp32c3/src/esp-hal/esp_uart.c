/**
 * @file        arch/riscv32/esp32c3/src/esp-hal/esp_uart.c
 * @brief       Console output via USB-Serial-JTAG (preferred) or UART0
 *
 * Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "esp_uart.h"
#include "esp_regs.h"

void esp_console_init(void)
{
  /* USB-Serial-JTAG is ready after ROM boot; UART0 left at ROM defaults. */
}

void esp_console_putc(char c)
{
  unsigned int spins;

  if (c == '\n') {
    esp_console_putc('\r');
  }

  /* Wait briefly for USB-Serial-JTAG IN endpoint space, then write. */
  for (spins = 0; spins < 100000u; spins++) {
    if (REG32(USB_SERIAL_JTAG_EP1_CONF_REG) & USB_SERIAL_JTAG_SERIAL_IN_EP_DATA_FREE) {
      REG32(USB_SERIAL_JTAG_EP1_REG) = (uint32_t)(uint8_t)c;
      REG32(USB_SERIAL_JTAG_EP1_CONF_REG) = USB_SERIAL_JTAG_WR_DONE;
      return;
    }
  }

  /* Fallback: UART0 FIFO (TX) — useful if an external UART is wired. */
  spins = 0;
  while (UART_TXFIFO_CNT(REG32(UART_STATUS_REG(0))) >= 126) {
    if (++spins > 100000u) {
      return;
    }
  }
  REG32(UART_FIFO_REG(0)) = (uint32_t)(uint8_t)c;
}

void esp_console_write(const char *s, unsigned int n)
{
  unsigned int i;

  for (i = 0; i < n; i++) {
    esp_console_putc(s[i]);
  }
}
