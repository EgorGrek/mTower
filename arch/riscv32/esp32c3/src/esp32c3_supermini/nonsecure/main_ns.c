/**
 * @file        arch/riscv32/esp32c3/src/esp32c3_supermini/nonsecure/main_ns.c
 * @brief       ESP32-C3 Super Mini Normal-World entry (FreeRTOS + hello)
 *
 * Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "FreeRTOS.h"
#include "task.h"

#include "printf.h"
#include "esp_uart.h"
#include "esp_gpio.h"
#include "esp_systimer.h"

#define HELLO_TASK_PRIORITY   (tskIDLE_PRIORITY + 2)
#define HELLO_TASK_STACK      512

extern BaseType_t xPortFreeRTOSInit(StackType_t xIsrTop);

static __attribute__((aligned(16))) StackType_t xISRStack[configISR_STACK_SIZE_WORDS];

static void hello_task(void *pvParameters)
{
  int count = 0;

  (void)pvParameters;

  for (;;) {
    printf("mTower ESP32-C3 Super Mini: hello_world #%d\n", count++);
    esp_led_set(count & 1);
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

#ifdef CONFIG_APPS_HELLO_WORLD
/* Optional: full TEE Client hello (requires Secure World — Phase 2). */
extern int tee_hello_world(void);

static void tee_hello_task(void *pvParameters)
{
  (void)pvParameters;
  printf("TEE hello_world skipped (Secure World not enabled in Phase 1)\n");
  vTaskDelete(NULL);
}
#endif

void _putchar(char character)
{
  esp_console_putc(character);
}

int main(void)
{
  esp_console_init();
  esp_systimer_init();
  esp_led_init();

  if (xPortFreeRTOSInit((StackType_t)&xISRStack[
          ((configISR_STACK_SIZE_WORDS - 1) & ~portBYTE_ALIGNMENT_MASK)]) != 0) {
    esp_console_write("xPortFreeRTOSInit failed\n", 25);
    for (;;) {
    }
  }

  printf("\n");
  printf("+---------------------------------------------+\n");
  printf("|  mTower ESP32-C3 Super Mini (Phase 1)       |\n");
  printf("|  FreeRTOS Normal World                      |\n");
  printf("+---------------------------------------------+\n");

  xTaskCreate(hello_task, "hello", HELLO_TASK_STACK, NULL,
              HELLO_TASK_PRIORITY, NULL);

#ifdef CONFIG_APPS_HELLO_WORLD
  xTaskCreate(tee_hello_task, "tee_hello", HELLO_TASK_STACK, NULL,
              HELLO_TASK_PRIORITY, NULL);
#endif

  vTaskStartScheduler();

  for (;;) {
  }

  return 0;
}
