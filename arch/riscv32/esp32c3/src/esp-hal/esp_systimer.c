/**
 * @file        arch/riscv32/esp32c3/src/esp-hal/esp_systimer.c
 * @brief       Read ESP32-C3 SYSTIMER unit0
 *
 * Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "esp_systimer.h"
#include "esp_regs.h"

void esp_systimer_init(void)
{
  /* Unit0 is enabled by ROM; ensure update works. */
  REG32(SYSTIMER_CONF_REG) |= (1u << 30); /* clk_en */
}

uint64_t esp_systimer_get_ticks(void)
{
  uint32_t hi;
  uint32_t lo;
  uint32_t hi2;

  REG32(SYSTIMER_UNIT0_OP_REG) = SYSTIMER_TIMER_UNIT0_UPDATE_M;
  while ((REG32(SYSTIMER_UNIT0_OP_REG) & SYSTIMER_TIMER_UNIT0_VALUE_VALID_M) == 0) {
  }

  do {
    hi = REG32(SYSTIMER_UNIT0_VALUE_HI_REG);
    lo = REG32(SYSTIMER_UNIT0_VALUE_LO_REG);
    hi2 = REG32(SYSTIMER_UNIT0_VALUE_HI_REG);
  } while (hi != hi2);

  return ((uint64_t)hi << 32) | lo;
}
