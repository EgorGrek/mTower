# mTower reference

Companion to [SKILL.md](SKILL.md). Prefer reading this only when the task needs
platform details, API status, Kconfig menus, or porting/app wiring depth.

## Platforms

| Platform | `PLATFORM` | Guide | Notes |
|----------|------------|-------|-------|
| NuMaker-PFM-M2351 | `numaker_pfm_m2351` | `docs/numaker_pfm_m2351.md` | Flash via NuMicro ICP (Windows): `mtower_s.hex` + `mtower_ns.hex` |
| M2351-Badge | `m2351_badge` | `docs/m2351_badge.md` | Same M2351 family |
| V2M-MPS2 QEMU | `mps2_an505_qemu` | `docs/v2m-mps2-qemu.md` | Needs `qemu-system-arm`; `make debug`; consoles `nc 127.0.0.1 1235/1236` |
| SparkFun RED-V | `sparkfun_redboard` | `docs/sparkfun_redboard.md` | SiFive FE310; flash/JLINK TBD in docs |
| Pine64 Ox64 | `pine64_ox64` | `docs/pine64_ox64.md` | BL808; `make flash`; BLDevCube TBD |
| ESP32-C3 Super Mini | `esp32c3_supermini` | `docs/esp32c3_supermini.md` | Phase 1 NS FreeRTOS; ESP HAL (not Metal); `esptool load_ram` |

Maintained (README): v0.6.0 era for listed platforms. `docs/build.md` table may
list older “Maintained” versions — prefer README for platform flags.

### Arch layout examples

```
arch/cortex-m23/m2351/src/numaker_pfm_m2351/{secure,nonsecure,partition_M2351.h}
arch/cortex-m33/.../mps2_an505_qemu/...
arch/riscv32/fe310/src/sparkfun_redboard/...
arch/riscv32/bl808/src/pine64_ox64/...
arch/riscv32/esp32c3/src/esp32c3_supermini/...
```

Typical platform `src` contents: `CMSIS`, `Device`, `StdDriver` (vendor), and
`<platform>` with user secure/nonsecure apps and makefiles. Partition / SAU /
memory attribution files are security-critical and platform-specific.

## Secure / Normal World interaction

- Normal World: FreeRTOS tasks; Client API in `tee_client/libteec` and
  `tee_client/public/` (`tee_client_api.h`, `tee_types.h`, …).
- Secure World: TA entry points + Internal API under `tee/` (`include`,
  `kernel`, `lib`, `tee`).
- Client–server: NS opens context/session and invokes commands; S handles them.

## GP TEE Client API status

| Function | Status |
|----------|--------|
| TEEC_InitializeContext | Yes (tested) |
| TEEC_FinalizeContext | Yes (tested) |
| TEEC_RegisterSharedMemory | No |
| TEEC_AllocateSharedMemory | Yes (tested) |
| TEEC_ReleaseSharedMemory | Yes (tested) |
| TEEC_OpenSession | Yes (tested) |
| TEEC_CloseSession | Yes (tested) |
| TEEC_InvokeCommand | Yes (tested) |
| TEEC_RequestCancellation | No |
| TEEC_PARAM_TYPES | Yes (not tested) |

Specs under `docs/specs/gp/` when present (Client + Internal API PDFs).

## GP TEE Internal API (summary)

**Yes (selected):** TA interface entry points; `TEE_Panic` (stub);
`TEE_OpenTASession` / `Close` / `InvokeTACommand`; `TEE_Malloc` / `Realloc` /
`Free` / `MemMove` / `MemCompare` / `MemFill`; large parts of object/storage
APIs; crypto operation allocate/free/set key; SHA digest; AES cipher; SHA MAC.

**No (selected groups):** Property access; cancellation; memory access-rights /
instance data; `TEE_GenerateKey`; AE; asymmetric; key derivation; random; time;
entire TEE Arithmetical API.

When analyzing “is X supported?”, prefer the tables in
`docs/mtower_functionality_description.md` over guessing from headers alone.

## Kconfig menus (high level)

From functionality description:

- **Build setup** — optimization (default -O1 is the reliable choice), debug
  output levels, assertions, symbols, TEE Internal/Client trace levels.
- **Trusted boot** — enable/disable loaders and start addresses.
- **System type** — arch/family/platform, UART colors, SAU/GPIO/SRAM/Flash
  secure attribution, peripheral/interrupt secure assignment, toolchain
  (GCC 6.1q1 / 6.1q2 / 8q4 historically).
- **Application configuration** — which apps/tests to bake into images
  (from `apps/Kconfig`).

Commands: `make menuconfig`, `make savedefconfig`, `make savedefmakedefs`.

## Porting a new platform (checklist)

Source: `docs/port-new-platform.md`.

1. If new arch: extend `arch/Kconfig` and add `arch/<arch>/`.
2. If new family: add under arch + wire family `Kconfig`.
3. Always: add `arch/.../src/<platform>/` (clone existing), including partition
   / attribution header and secure/nonsecure makefiles.
4. Clone `configs/<existing>` → `configs/<newdev>` (`defconfig`, `Make.defs`).
5. `make menuconfig` / `make savedefconfig` / `make savedefmakedefs` as needed.
6. For upstream: update `README.md`, `docs/build.md`, add `docs/<newdev>.md`,
   update `AUTHORS` if becoming maintainer.

## Adding an app (checklist)

Source: `docs/add-new-app.md`.

1. Copy `apps/hello_world` → `apps/<name>`.
2. Add `config APPS_<NAME>` to `apps/Kconfig`.
3. Generate UUID in `<name>_ta.h`.
4. Implement `ca/` and `ta/`.
5. Platform wiring:
   - `nonsecure/main_ns.c` — `xTaskCreate` under `#ifdef CONFIG_APPS_...`
   - `nonsecure/Make.defs` — `CHIP_CSRCS_NS += .../ca/...`
   - `nonsecure/Makefile` — include path
   - `secure/Make.defs` — `CHIP_CSRCS_S += .../ta/...`
   - `secure/Makefile` — include path
6. `make clean; make menuconfig; make`.

## Build path (Makefile)

Top-level `Makefile` resolves:

```
ARCH_DIR = arch/$(CONFIG_ARCH)/$(CONFIG_ARCH_FAMILY)
ARCH_SRC = $(ARCH_DIR)/src/$(CONFIG_PLATFORM)
```

Requires `.config` and `Make.defs` from `create_context`. Toolchain unpack
target: `make toolchain`.

## Related docs not linked from README contents

Still useful when analyzing:

- `docs/add-new-app.md`
- `docs/mtower_test_suite_description.md`
- `docs/mtower_hw_security_exception_example.md`
