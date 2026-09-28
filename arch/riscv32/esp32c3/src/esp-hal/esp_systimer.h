/**
 * @file        arch/riscv32/esp32c3/src/esp-hal/esp_systimer.h
 * @brief       SYSTIMER helpers for cooperative FreeRTOS tick
 *
 * Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#ifndef __ARCH_RISCV32_ESP32C3_SRC_ESP_HAL_ESP_SYSTIMER_H
#define __ARCH_RISCV32_ESP32C3_SRC_ESP_HAL_ESP_SYSTIMER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void esp_systimer_init(void);
uint64_t esp_systimer_get_ticks(void);

/* Approximate SYSTIMER frequency after ROM clock init (16 MHz). */
#define ESP_SYSTIMER_HZ 16000000ULL

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_RISCV32_ESP32C3_SRC_ESP_HAL_ESP_SYSTIMER_H */
