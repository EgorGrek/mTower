/**
 * @file        arch/riscv32/esp32c3/src/esp-hal/esp_regs.h
 * @brief       Minimal ESP32-C3 MMIO register map for mTower BSP
 *
 * Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#ifndef __ARCH_RISCV32_ESP32C3_SRC_ESP_HAL_ESP_REGS_H
#define __ARCH_RISCV32_ESP32C3_SRC_ESP_HAL_ESP_REGS_H

#include <stdint.h>

/* Peripheral bases (ESP32-C3 TRM). */
#define DR_REG_UART0_BASE           0x60000000u
#define DR_REG_GPIO_BASE            0x60004000u
#define DR_REG_SYSTIMER_BASE        0x60023000u
#define DR_REG_USB_SERIAL_JTAG_BASE 0x60043000u
#define DR_REG_SYSTEM_BASE          0x600C0000u
#define DR_REG_IO_MUX_BASE          0x60009000u

#define REG32(addr) (*(volatile uint32_t *)(uintptr_t)(addr))

/* UART0 */
#define UART_FIFO_REG(n)        (DR_REG_UART0_BASE + (n) * 0x10000u + 0x0000u)
#define UART_INT_ST_REG(n)      (DR_REG_UART0_BASE + (n) * 0x10000u + 0x0008u)
#define UART_INT_ENA_REG(n)     (DR_REG_UART0_BASE + (n) * 0x10000u + 0x000Cu)
#define UART_INT_CLR_REG(n)     (DR_REG_UART0_BASE + (n) * 0x10000u + 0x0010u)
#define UART_CLKDIV_REG(n)      (DR_REG_UART0_BASE + (n) * 0x10000u + 0x0014u)
#define UART_STATUS_REG(n)      (DR_REG_UART0_BASE + (n) * 0x10000u + 0x001Cu)
#define UART_CONF0_REG(n)       (DR_REG_UART0_BASE + (n) * 0x10000u + 0x0020u)
#define UART_CONF1_REG(n)       (DR_REG_UART0_BASE + (n) * 0x10000u + 0x0024u)
#define UART_CLK_CONF_REG(n)    (DR_REG_UART0_BASE + (n) * 0x10000u + 0x0078u)

#define UART_TXFIFO_CNT_M       0x000000FFu
#define UART_TXFIFO_CNT_S       16
#define UART_TXFIFO_CNT(status) (((status) >> UART_TXFIFO_CNT_S) & UART_TXFIFO_CNT_M)

/* USB Serial/JTAG (console on many Super Mini boards). */
#define USB_SERIAL_JTAG_EP1_REG           (DR_REG_USB_SERIAL_JTAG_BASE + 0x0000u)
#define USB_SERIAL_JTAG_EP1_CONF_REG      (DR_REG_USB_SERIAL_JTAG_BASE + 0x0004u)
#define USB_SERIAL_JTAG_WR_DONE           (1u << 0)
#define USB_SERIAL_JTAG_SERIAL_IN_EP_DATA_FREE (1u << 1)

/* SYSTIMER unit0 (16 MHz typical). */
#define SYSTIMER_CONF_REG             (DR_REG_SYSTIMER_BASE + 0x0000u)
#define SYSTIMER_UNIT0_OP_REG         (DR_REG_SYSTIMER_BASE + 0x0004u)
#define SYSTIMER_UNIT0_LOAD_HI_REG    (DR_REG_SYSTIMER_BASE + 0x000Cu)
#define SYSTIMER_UNIT0_LOAD_LO_REG    (DR_REG_SYSTIMER_BASE + 0x0010u)
#define SYSTIMER_UNIT0_VALUE_HI_REG   (DR_REG_SYSTIMER_BASE + 0x0040u)
#define SYSTIMER_UNIT0_VALUE_LO_REG   (DR_REG_SYSTIMER_BASE + 0x0044u)
#define SYSTIMER_UNIT0_LOAD_REG       (DR_REG_SYSTIMER_BASE + 0x005Cu)

#define SYSTIMER_TIMER_UNIT0_UPDATE_M  (1u << 30)
#define SYSTIMER_TIMER_UNIT0_VALUE_VALID_M (1u << 29)

/* GPIO */
#define GPIO_OUT_W1TS_REG         (DR_REG_GPIO_BASE + 0x0008u)
#define GPIO_OUT_W1TC_REG         (DR_REG_GPIO_BASE + 0x000Cu)
#define GPIO_ENABLE_W1TS_REG      (DR_REG_GPIO_BASE + 0x0024u)

/* Super Mini often wires a user LED on GPIO8. */
#define ESP32C3_LED_GPIO          8

#endif /* __ARCH_RISCV32_ESP32C3_SRC_ESP_HAL_ESP_REGS_H */
