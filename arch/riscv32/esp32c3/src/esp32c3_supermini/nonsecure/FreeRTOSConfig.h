/**
 * @file        arch/riscv32/esp32c3/src/esp32c3_supermini/nonsecure/FreeRTOSConfig.h
 * @brief       FreeRTOS configuration for ESP32-C3 Super Mini (Phase 1)
 *
 * Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configCLINT_BASE_ADDRESS		0
#define configUSE_PREEMPTION			0
#define configUSE_IDLE_HOOK			1
#define configUSE_TICK_HOOK			0
#define configCPU_CLOCK_HZ			( 160000000UL )
#define configTICK_RATE_HZ			( ( TickType_t ) 100 )
#define configMAX_PRIORITIES			( 7 )

#ifdef __riscv_fdiv
#define configENABLE_FPU	1
#else
#define configENABLE_FPU	0
#endif

#ifdef __riscv_fdiv
#define configMINIMAL_STACK_SIZE		( ( size_t ) 288 )
#else
#define configMINIMAL_STACK_SIZE		( ( size_t ) 256 )
#endif

#define configAPPLICATION_ALLOCATED_HEAP 	1
#define configTOTAL_HEAP_SIZE          		( ( size_t ) 8192 )

#define configMAX_TASK_NAME_LEN				( 16 )
#define configUSE_TRACE_FACILITY			0
#define configUSE_16_BIT_TICKS				0
#define configIDLE_SHOULD_YIELD				1
#define configUSE_MUTEXES					1
#define configQUEUE_REGISTRY_SIZE			8
#define configCHECK_FOR_STACK_OVERFLOW		2
#define configUSE_RECURSIVE_MUTEXES			1
#define configUSE_MALLOC_FAILED_HOOK		1
#define configUSE_APPLICATION_TASK_TAG		0
#define configUSE_COUNTING_SEMAPHORES		1
#define configGENERATE_RUN_TIME_STATS		0
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0
#define portUSING_MPU_WRAPPERS				0

#define configUSE_NEWLIB_REENTRANT 		0

#define configUSE_CO_ROUTINES 				0
#define configMAX_CO_ROUTINE_PRIORITIES 	( 2 )

#define configUSE_TIMERS				0
#define configTIMER_TASK_PRIORITY		( configMAX_PRIORITIES - 1 )
#define configTIMER_QUEUE_LENGTH		4
#define configTIMER_TASK_STACK_DEPTH		( 256 )

#define INCLUDE_vTaskPrioritySet		1
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	1
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1
#define INCLUDE_eTaskGetState			1
#define INCLUDE_xTimerPendFunctionCall	0

/* ISR stack for FreeRTOS RISC-V port (xPortFreeRTOSInit). */
#define configISR_STACK_SIZE_WORDS		( 256 )

#endif /* FREERTOS_CONFIG_H */
