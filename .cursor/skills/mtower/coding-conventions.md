# mTower coding conventions (condensed)

Full guide: `docs/mtower-coding-standard.md`. Apply these when editing or
reviewing C in this repo.

## Files

- Every `.c` / `.h` / `Makefile` / `.sh` starts with a file header (`@file`
  relative path, optional `@brief`, copyright, Apache-2.0 or as required).
- Headers: include guards from relative path, e.g. `include/crypto/aes.h` →
  `__INCLUDE_CRYPTO_AES_H`.
- C source section order: Includes → Macros → Private types → Private prototypes
  → Private data → Public data → Private functions → Public functions.
- Header section order: Includes → Macros → Public types → Public data → Inline
  → Public prototypes.
- Line endings `\n`; no trailing whitespace; max ~80 columns; end file with
  newline.

## Comments

- C89 `/* */` only (no `//`) outside arch-specific exceptions.
- Single-line: `/* comment. */`
- Multi-line: opening `/*` on first line; continuation lines start with ` *`;
  closing `*/` alone on last line.
- Disable large blocks with `#if 0` + explaining comment, not comments.
- Prefer doxygen `/**` / `/**<` for structs and APIs.

## Formatting

- Indent: **2 spaces**.
- Control braces: opening `{` on same line as `if`/`while`/`for`/`switch`/`do`.
- Function braces: `{` on its own line, column 1.
- Space after keywords before `(`: `if (x)`, `for (i = 0; ...)`.
- No space between function name and `(`: `foo(x)`.
- Spaces around binary operators.
- One statement / one declaration per line; no multi-assign in one statement.
- Preprocessor: `#` in column 1; indent directives as `#  define` inside `#ifdef`.

## Naming

| Kind | Rule | Example |
|------|------|---------|
| Struct | `*_s`, module prefix | `struct xyz_info_s` |
| Enum type | `*_e` | `enum xyz_state_e` |
| Enum values | UPPER_SNAKE with prefix | `XYZ_STATE_BUSY` |
| Typedef | `*_t` | `myhandle_t` |
| Global | short, often `g_`, prefer struct wrap | `g_myvariables` |
| Function | module prefix + lowerCamel / terse | `xyz_putvalue` |
| Macro | UPPER_SNAKE; paren args; statements in `do { } while (0)` | `MAX(a,b)` |

Locals/params: terse lowerCamel; `i`/`j`/`k` only as loop indices; `ret` common
for return/status.

## Functions

- Blank line, then function header comment (name, params `[in]`/`[out]`, returns
  including errors), blank line, then definition.
- Keep functions short (ideally one screen).
- Internal OS-style returns: non-negative success, negative errno (see
  `include/jerrno.h` where used). Always check `malloc`/`realloc`.
- Cast unused returns to `(void)` intentionally.
- `goto` only for nested error cleanup; labels in column 1, lowercase.

## Example snippets

```c
int do_foobar(void)
{
  int ret = 0;
  int i;

  for (i = 0; i < 5 || ret < 10; i++) {
    ret = foobar(i);
  }

  return ret;
}
```

```c
#ifdef CONFIG_ABC
#  define ABC_THING1 1
#  define ABC_THING2 2
#endif
```
