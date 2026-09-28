/**
 * @file        arch/riscv32/esp32c3/src/esp-hal/esp_freertos_port.c
 * @brief       FreeRTOS glue for ESP32-C3 (cooperative tick via SYSTIMER)
 *
 * Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "FreeRTOS.h"
#include "task.h"

#include "esp_systimer.h"
#include "esp_uart.h"

/* Application-provided heap for heap_4. */
uint8_t ucHeap[configTOTAL_HEAP_SIZE];

static uint64_t s_last_tick_time;

void esp_port_handle_interrupt(void)
{
  /* Phase 1: no external IRQ routing yet. */
}

void esp_port_handle_exception(void)
{
  /* Avoid nested faults from console MMIO while diagnosing. */
  for (;;) {
  }
}

void vPortSetupTimerInterrupt(void)
{
  esp_systimer_init();
  s_last_tick_time = esp_systimer_get_ticks();
}

void vApplicationIdleHook(void)
{
  uint64_t now;
  uint64_t elapsed;
  const uint64_t ticks_per_os_tick = ESP_SYSTIMER_HZ / configTICK_RATE_HZ;

  now = esp_systimer_get_ticks();
  if (now < s_last_tick_time) {
    s_last_tick_time = now;
    return;
  }

  elapsed = now - s_last_tick_time;
  while (elapsed >= ticks_per_os_tick) {
    s_last_tick_time += ticks_per_os_tick;
    elapsed -= ticks_per_os_tick;
    if (xTaskIncrementTick() != pdFALSE) {
      taskYIELD();
    }
  }
}

void vApplicationMallocFailedHook(void)
{
  esp_console_write("malloc failed\n", 14);
  for (;;) {
  }
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
  (void)xTask;
  (void)pcTaskName;
  esp_console_write("stack overflow\n", 15);
  for (;;) {
  }
}

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                   StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize)
{
  /* Dynamic allocation path — not used when static alloc disabled. */
  (void)ppxIdleTaskTCBBuffer;
  (void)ppxIdleTaskStackBuffer;
  (void)pulIdleTaskStackSize;
}
