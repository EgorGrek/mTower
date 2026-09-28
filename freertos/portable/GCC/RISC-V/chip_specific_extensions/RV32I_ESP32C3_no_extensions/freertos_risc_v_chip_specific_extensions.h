/*
 * FreeRTOS RISC-V chip-specific extensions for ESP32-C3 (no CLINT/mtime).
 * Phase 1 uses cooperative scheduling with SYSTIMER polled from idle hook.
 */

#ifndef __FREERTOS_RISC_V_EXTENSIONS_H__
#define __FREERTOS_RISC_V_EXTENSIONS_H__

#define portasmHAS_CLINT 0
#define portasmHAS_MTIME 0
#define portasmHAS_SIFIVE_CLINT 0
/* ESP32-C3 interrupt enables are not classic RISC-V mie; writing mie traps. */
#define portasmHAS_STANDARD_MIE 0
#define portasmADDITIONAL_CONTEXT_SIZE 0

.macro portasmSAVE_ADDITIONAL_REGISTERS
	.endm

.macro portasmRESTORE_ADDITIONAL_REGISTERS
	.endm

#endif /* __FREERTOS_RISC_V_EXTENSIONS_H__ */
