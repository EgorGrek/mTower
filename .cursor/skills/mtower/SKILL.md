---
name: mtower
description: >-
  Navigate, analyze, build, and modify Samsung mTower — a lightweight TEE for
  size-constrained IoT MCUs (Cortex-M23/M33 and RISC-V). Use when working in
  this repository, exploring Secure/Normal World code, TEE Client/Internal API,
  platforms, apps, configs, build/Kconfig, porting, or coding-standard questions.
---

# mTower Project Skill

## What mTower is

mTower is a Trusted Execution Environment for constrained IoT devices. It splits
execution into:

| World | Role | Stack |
|-------|------|-------|
| **Secure World** | TEE server / Trusted Applications (TAs) | Event-handler style; GP TEE Internal API |
| **Normal World** | Client apps under FreeRTOS | GP TEE Client API (`tee_client`) |

Apps call Secure World via Client API (`TEEC_*`). TAs implement entry points
(`TA_CreateEntryPoint`, `TA_OpenSessionEntryPoint`, `TA_InvokeCommandEntryPoint`, …).

Upstream: https://github.com/Samsung/mTower  
License: Apache-2.0 for mTower code; see `COPYING` / per-file headers for third-party terms.

## When analyzing this codebase

Follow this order unless the user points elsewhere:

1. **Identify the concern** — platform, TEE kernel, Client API, crypto, app, build, or docs.
2. **Map to directories** using the layout below.
3. **Read platform config** — `configs/<platform>/{defconfig,Make.defs}` and
   `arch/<arch>/<family>/src/<platform>/{secure,nonsecure}/`.
4. **Trace Secure ↔ Normal** — CA in `apps/*/ca`, TA in `apps/*/ta`, API in
   `tee_client/` and `tee/`.
5. **Check docs** — `docs/` for build, porting, apps, API status, tests.
6. **Note incomplete areas** — several platform flash/run sections and some GP
   APIs are stubs or unimplemented (see [reference.md](reference.md)).

## Directory map (start here)

```
apps/           Sample CAs/TAs (hello_world, hotp, aes, test)
arch/           Arch + board ports
  cortex-m23/   M2351 boards (numaker_pfm_m2351, m2351_badge)
  cortex-m33/   MPS2 AN505 QEMU
  riscv32/      fe310 (sparkfun_redboard), bl808 (pine64_ox64), esp32c3 (esp32c3_supermini)
configs/        Per-platform defconfig + Make.defs
tee/            TEE Internal API / kernel / secure libs
tee_client/     GP TEE Client API (libteec + public headers)
crypto/         Crypto support
freertos/       Normal-world RTOS
include/        Shared headers (include/mtower/)
common/         Shared common code
tools/          Build helpers (mkconfig, etc.)
docs/           Project documentation
```

Path formula for a board:

`arch/$(CONFIG_ARCH)/$(CONFIG_ARCH_FAMILY)/src/$(CONFIG_PLATFORM)/`

Secure and non-secure worlds live under that path as `secure/` and `nonsecure/`
(linker scripts, `main.c` / `main_ns.c`, `Make.defs`, partition headers).

## Platforms

Pass `PLATFORM=<flag>` when creating context:

| Board | `PLATFORM=` | Arch path |
|-------|-------------|-----------|
| NuMaker-PFM-M2351 | `numaker_pfm_m2351` | `arch/cortex-m23/m2351/...` |
| M2351-Badge | `m2351_badge` | `arch/cortex-m23/m2351/...` |
| V2M-MPS2 (QEMU) | `mps2_an505_qemu` | `arch/cortex-m33/...` |
| SparkFun RED-V | `sparkfun_redboard` | `arch/riscv32/fe310/...` |
| Pine64 Ox64 | `pine64_ox64` | `arch/riscv32/bl808/...` |
| ESP32-C3 Super Mini | `esp32c3_supermini` | `arch/riscv32/esp32c3/...` |

Platform how-tos: `docs/<platform>.md`. Porting: `docs/port-new-platform.md`.

## Build workflow

```sh
# 1. Context from platform defconfig
make PLATFORM=<flag> create_context

# 2. Download toolchain into toolchain/
make toolchain

# 3. Optional config
make menuconfig          # then make savedefconfig if saving defaults

# 4. Build
make                     # V=1 for verbose

# Docs
make docs_gen && make docs_show
```

Prerequisites (Ubuntu-oriented): see `docs/build.md` (git, gcc, make, doxygen,
kconfig-frontends optional for `menuconfig`, multilib, etc.).

Flash/run is platform-specific (`docs/numaker_pfm_m2351.md`, QEMU `make debug`,
Ox64 `make flash`, …). RISC-V board docs may still mark flash steps as TBD.

## Application model

- Apps are **statically linked** into Secure and/or Non-secure images (not dynamically loaded).
- Layout: `apps/<name>/{ca,ta,<name>_ta.h}` — clone `apps/hello_world` as template.
- Wire into build: `apps/Kconfig`, platform `nonsecure`/`secure` `Make.defs` +
  `Makefile`, and FreeRTOS `xTaskCreate` in `main_ns.c`.
- Unique TA UUID in the app header. Full steps: `docs/add-new-app.md`.
- **User-TAs** use TEE Internal API; **Pseudo-TAs** may not.

## GP TEE API (analysis cheat sheet)

**Client API implemented:** `TEEC_InitializeContext`, `FinalizeContext`,
`AllocateSharedMemory`, `ReleaseSharedMemory`, `OpenSession`, `CloseSession`,
`InvokeCommand`, `TEEC_PARAM_TYPES`.

**Client API missing:** `TEEC_RegisterSharedMemory`, `TEEC_RequestCancellation`.

**Internal highlights implemented:** TA entry points, panic stub, TA-to-TA
session calls, malloc/free/mem*, much of object/storage API, digest (SHA),
cipher (AES), MAC (SHA).

**Often missing / No:** AE, asymmetric crypto, key derive, random, time API,
arithmetical API, many property accessors, cancellation, memory access-rights
helpers. Crypto notes: digest/MAC = SHA; cipher = AES.

Full matrix: `docs/mtower_functionality_description.md` and
[reference.md](reference.md).

## Tests

GP API tests live under `apps/test`. Build with `make menuconfig` → Application
configuration → GP API test suite, then `make clean; make`. Prefer adding tests
when changing TEE API behavior (`docs/mtower_test_suite_description.md`).

## Coding rules (enforce on edits)

Distilled from `docs/mtower-coding-standard.md` — details in
[coding-conventions.md](coding-conventions.md):

- C89 outside arch-specific code; **no `//` comments**
- 2-space indent; ~80 columns; Unix `\n` endings
- File header (`@file`, copyright, license); doxygen-style function headers
- Naming: structs `*_s`, enums `*_e`, typedefs `*_t`, globals often `g_*`,
  module prefix `xyz_`
- Brace style: K&R for control flow; function `{` on its own line
- `#` stays in column 1; indent body of `#if` with `#  define`

## Analysis / change checklists

**Explaining a feature**
- [ ] Locate CA ↔ TA ↔ TEE kernel path
- [ ] Note which GP APIs are used and whether implemented
- [ ] Cite platform-specific code if behavior differs by board

**Fixing or adding code**
- [ ] Match coding standard
- [ ] Update `apps/Kconfig` / platform Make.defs if new sources
- [ ] Consider GP test coverage for TEE API changes
- [ ] For new platforms: arch Kconfig + `configs/` + README/build.md + board doc

**Reviewing a change**
- [ ] Secure vs non-secure boundary respected
- [ ] No magic numbers; errors via defined errno-style negatives where applicable
- [ ] License/header present on new files

## Contributing notes

Issue-linked branches (`999-description`), update `ReleaseNotes` for non-trivial
changes, PR against upstream master. See `.github/CONTRIBUTING.md`.

## Doc index (read on demand)

| Doc | Use when |
|-----|----------|
| `README.md` | Project overview |
| `docs/build.md` | Build prerequisites and flow |
| `docs/source-code-structure.md` | Tree explanation |
| `docs/mtower_functionality_description.md` | H/W + GP API + Kconfig options |
| `docs/mtower-coding-standard.md` | Full style guide |
| `docs/port-new-platform.md` | New board/arch |
| `docs/add-new-app.md` | New CA/TA |
| `docs/mtower_test_suite_description.md` | Running API tests |
| `docs/<platform>.md` | Flash/run for a board |
| [reference.md](reference.md) | Platforms, API status, Kconfig menus |
| [coding-conventions.md](coding-conventions.md) | Condensed style rules |
