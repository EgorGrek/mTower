############################################################################
# arch/riscv32/esp32c3/src/Makefile
#
# Copyright (c) 2026 Samsung Electronics Co., Ltd. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
############################################################################

-include $(TOPDIR)/Make.defs
-include $(TOPDIR)/.config

# Platform build is driven from esp32c3_supermini/Makefile via ARCH_SRC.

clean:
	$(Q) $(MAKE) -C $(CONFIG_PLATFORM) TOPDIR="$(TOPDIR)" clean

distclean: clean
