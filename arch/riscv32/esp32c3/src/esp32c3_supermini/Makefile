############################################################################
# arch/riscv32/esp32c3/src/esp32c3_supermini/Makefile
#
# Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
############################################################################

-include $(TOPDIR)/Make.defs
-include $(TOPDIR)/.config
-include Make.defs

MTOWER_NS = $(TOPDIR)/mtower_ns.bin

ifeq ($(CONFIG_BOOTLOADER33),y)
BL33 := $(TOPDIR)/build/nonsecure$(subst $(TOPDIR),,$(shell pwd))/nonsecure/bl33.bin
else
BL33 := null
endif

mtower$(EXEEXT):
ifeq ($(CONFIG_BOOTLOADER33),y)
	$(Q) $(MAKE) -C nonsecure TOPDIR="$(TOPDIR)" mtower_ns$(EXEEXT)
endif
ifeq ($(CONFIG_BOOTLOADER33),y)
	$(eval bl33_sz = `stat -c%s $(TOPDIR)/build/nonsecure$(subst $(TOPDIR),,$(shell pwd))/nonsecure/bl33.bin`)
	$(eval bl33_start = $(CONFIG_START_ADDRESS_BL33))
	$(Q) printf "$(GREEN)+-----------------------------------------------------------------------+$(NORMAL)\n"
	$(Q) printf "$(GREEN)| Non-Secure image (ESP32-C3 Super Mini)                                |$(NORMAL)\n"
	$(Q) printf "$(GREEN)+-----------------------------------------------------------------------+$(NORMAL)\n"
	$(Q) printf "$(GREEN)| FreeRTOS        | 0x%08x | size %u | bl33.bin / mtower_ns.bin |$(NORMAL)\n" $(bl33_start) $(bl33_sz)
	$(Q) printf "$(GREEN)+-----------------------------------------------------------------------+$(NORMAL)\n"
endif

clean:
	$(Q) $(MAKE) -C nonsecure TOPDIR="$(TOPDIR)" clean
	$(Q) rm -rf $(TOPDIR)/build
	$(Q) rm -f $(TOPDIR)/mtower_ns.bin $(TOPDIR)/mtower_ns.elf $(TOPDIR)/mtower_ns_ram.bin

distclean: clean

# Flash via project .venv-esptool (preferred) or esptool on PATH.
# Phase 1: convert ELF -> ESP image (magic 0xE9), then load-ram.
# Do NOT write_flash the raw .bin to 0x0 (that overwrites the ROM bootloader slot).
ifeq ($(wildcard $(TOPDIR)/.venv-esptool/bin/esptool),)
  ifeq ($(wildcard $(TOPDIR)/.venv-esptool/bin/esptool.py),)
    ESPTOOL ?= esptool.py
  else
    ESPTOOL ?= $(TOPDIR)/.venv-esptool/bin/esptool.py
  endif
else
  ESPTOOL ?= $(TOPDIR)/.venv-esptool/bin/esptool
endif
ESP_PORT ?= /dev/ttyACM0
ESP_BAUD ?= 460800

$(TOPDIR)/mtower_ns_ram.bin: $(TOPDIR)/mtower_ns.elf
	@echo "IMG: elf2image --ram-only-header -> $@"
	$(Q) $(ESPTOOL) --chip esp32c3 elf2image --ram-only-header \
		-o $(TOPDIR)/mtower_ns_ram.bin $(TOPDIR)/mtower_ns.elf

flash: $(TOPDIR)/mtower_ns_ram.bin
	@echo "FLASH: load-ram $(TOPDIR)/mtower_ns_ram.bin via $(ESP_PORT)"
	$(Q) $(ESPTOOL) --chip esp32c3 --port $(ESP_PORT) --baud $(ESP_BAUD) \
		--no-stub load-ram $(TOPDIR)/mtower_ns_ram.bin

flash_ram: flash
