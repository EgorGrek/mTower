/**
 * @file        arch/riscv32/esp32c3/src/esp-hal/esp_gpio.h
 * @brief       Minimal GPIO for Super Mini LED
 *
 * Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#ifndef __ARCH_RISCV32_ESP32C3_SRC_ESP_HAL_ESP_GPIO_H
#define __ARCH_RISCV32_ESP32C3_SRC_ESP_HAL_ESP_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

void esp_led_init(void);
void esp_led_set(int on);

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_RISCV32_ESP32C3_SRC_ESP_HAL_ESP_GPIO_H */
