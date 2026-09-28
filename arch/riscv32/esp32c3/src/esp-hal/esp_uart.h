/**
 * @file        arch/riscv32/esp32c3/src/esp-hal/esp_uart.h
 * @brief       Console UART / USB-Serial-JTAG for ESP32-C3
 *
 * Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#ifndef __ARCH_RISCV32_ESP32C3_SRC_ESP_HAL_ESP_UART_H
#define __ARCH_RISCV32_ESP32C3_SRC_ESP_HAL_ESP_UART_H

#ifdef __cplusplus
extern "C" {
#endif

void esp_console_init(void);
void esp_console_putc(char c);
void esp_console_write(const char *s, unsigned int n);

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_RISCV32_ESP32C3_SRC_ESP_HAL_ESP_UART_H */
