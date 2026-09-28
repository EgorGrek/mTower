/**
 * @file        arch/riscv32/esp32c3/src/esp-hal/esp_gpio.c
 * @brief       Minimal GPIO for Super Mini LED
 *
 * Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "esp_regs.h"

void esp_led_init(void)
{
  REG32(GPIO_ENABLE_W1TS_REG) = (1u << ESP32C3_LED_GPIO);
}

void esp_led_set(int on)
{
  if (on) {
    REG32(GPIO_OUT_W1TS_REG) = (1u << ESP32C3_LED_GPIO);
  } else {
    REG32(GPIO_OUT_W1TC_REG) = (1u << ESP32C3_LED_GPIO);
  }
}
