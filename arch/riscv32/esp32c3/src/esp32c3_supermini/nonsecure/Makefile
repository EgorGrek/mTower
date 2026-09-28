############################################################################
# arch/riscv32/esp32c3/src/esp32c3_supermini/nonsecure/Makefile
#
# Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
############################################################################

-include $(TOPDIR)/Make.defs
-include $(TOPDIR)/.config
-include Make.defs

CFLAGS += -I../ -I./
CFLAGS += -I../../esp-hal
CFLAGS += -I$(TOPDIR)/include/mtower
CFLAGS += -I$(TOPDIR)/freertos/include
CFLAGS += -I$(TOPDIR)/freertos/portable/GCC/RISC-V
CFLAGS += -I$(TOPDIR)/freertos/portable/GCC/RISC-V/chip_specific_extensions/RV32I_ESP32C3_no_extensions

ifeq ($(CONFIG_APPS_HELLO_WORLD),y)
CFLAGS += -I$(TOPDIR)/apps/hello_world
CFLAGS += -DCONFIG_APPS_HELLO_WORLD=1
endif

CFLAGS += -DDEBUG_PORT=$(subst ",,$(CONFIG_NONSECURE_DEBUG_UART))

OBJDIR = $(TOPDIR)/build/nonsecure$(subst $(TOPDIR),,$(shell pwd))

LIBPATHS = -L. -L"$(TOPDIR)/lib"
LIBS = -lFreeRTOS_ns -lgcc

$(OBJDIR)/esp_startup$(OBJEXT): ../../esp-hal/esp_startup.S
	$(Q) mkdir -p $(OBJDIR)
	@echo "AS: $<"
	$(Q) $(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/portASM$(OBJEXT): $(TOPDIR)/freertos/portable/GCC/RISC-V/portASM.S
	$(Q) mkdir -p $(OBJDIR)
	@echo "AS: $<"
	$(Q) $(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/main_ns$(OBJEXT): main_ns.c
	$(Q) mkdir -p $(OBJDIR)
	@echo "CC: $<"
	$(Q) $(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/printf$(OBJEXT): printf.c
	$(Q) mkdir -p $(OBJDIR)
	@echo "CC: $<"
	$(Q) $(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/esp_uart$(OBJEXT): ../../esp-hal/esp_uart.c
	$(Q) mkdir -p $(OBJDIR)
	@echo "CC: $<"
	$(Q) $(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/esp_systimer$(OBJEXT): ../../esp-hal/esp_systimer.c
	$(Q) mkdir -p $(OBJDIR)
	@echo "CC: $<"
	$(Q) $(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/esp_gpio$(OBJEXT): ../../esp-hal/esp_gpio.c
	$(Q) mkdir -p $(OBJDIR)
	@echo "CC: $<"
	$(Q) $(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/esp_freertos_port$(OBJEXT): ../../esp-hal/esp_freertos_port.c
	$(Q) mkdir -p $(OBJDIR)
	@echo "CC: $<"
	$(Q) $(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/libc_min$(OBJEXT): ../../esp-hal/libc_min.c
	$(Q) mkdir -p $(OBJDIR)
	@echo "CC: $<"
	$(Q) $(CC) -c $(CFLAGS) $< -o $@

mtower_ns$(EXEEXT): $(OBJDIR)/esp_startup$(OBJEXT) $(OBJDIR)/portASM$(OBJEXT) \
		$(OBJDIR)/main_ns$(OBJEXT) $(OBJDIR)/printf$(OBJEXT) \
		$(OBJDIR)/esp_uart$(OBJEXT) $(OBJDIR)/esp_systimer$(OBJEXT) \
		$(OBJDIR)/esp_gpio$(OBJEXT) $(OBJDIR)/esp_freertos_port$(OBJEXT) \
		$(OBJDIR)/libc_min$(OBJEXT)
	$(Q) $(MAKE) -C $(TOPDIR)/freertos/ TOPDIR="$(TOPDIR)" FREE_RTOS_ARCH=RISC-V libFreeRTOS_ns.a
	@echo "LD: mtower_ns$(EXEEXT)"
	$(Q) $(CC) $(CFLAGS) $(LDFLAGS) -nostartfiles -Tesp32c3.ld \
		$(OBJDIR)/esp_startup$(OBJEXT) $(OBJDIR)/portASM$(OBJEXT) \
		$(OBJDIR)/main_ns$(OBJEXT) $(OBJDIR)/printf$(OBJEXT) \
		$(OBJDIR)/esp_uart$(OBJEXT) $(OBJDIR)/esp_systimer$(OBJEXT) \
		$(OBJDIR)/esp_gpio$(OBJEXT) $(OBJDIR)/esp_freertos_port$(OBJEXT) \
		$(OBJDIR)/libc_min$(OBJEXT) \
		$(LIBPATHS) $(LIBS) -o $(OBJDIR)/bl33.elf
	$(Q) $(OBJCOPY) -S -O binary $(OBJDIR)/bl33.elf $(OBJDIR)/bl33.bin
	$(Q) $(OBJCOPY) -S -O ihex $(OBJDIR)/bl33.elf $(OBJDIR)/bl33.hex
	$(Q) cp -f $(OBJDIR)/bl33.bin $(TOPDIR)/mtower_ns.bin
	$(Q) cp -f $(OBJDIR)/bl33.elf $(TOPDIR)/mtower_ns.elf
	$(Q) $(SIZE) $(OBJDIR)/bl33.elf

clean:
	$(Q) rm -f $(OBJDIR)/*$(OBJEXT) $(OBJDIR)/bl33.*

distclean: clean
