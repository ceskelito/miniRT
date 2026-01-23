---
name: 'The Norm'

description: 'Code writing rules and standards'

applyTo: "**.c,**.h"
---

# 42 C Coding Norm (v4.1) — AI‑Ready Summary

Authoritative, concise rules for automated checks and AI assistants. Paraphrased from the 42 Norm v4.1 to be machine‑friendly.

## IN CASE OF CONFLICT

- These rules take priority over any existing project style unless the project explicitly grants an exception.
- Project‑specific exceptions stated in the subject or evaluation guide override this summary.
- When unclear, prefer the stricter interpretation and keep code compiling.

## Priority Order (most → least critical)

1. Compiles cleanly; forbidden constructs not used.
2. Function size/complexity limits (lines, params, locals).
3. Formatting (line width, indentation, spacing, empty lines).
4. Naming schema and file organization.
5. Header/guard and preprocessor hygiene.
6. Comments policy and 42 file header presence.

---

## General Naming & Scope

- Identifiers: lowercase `snake_case`, ASCII only (variables, functions, types, macros per macro rules).
- Prefixes:
  - `s_` for `struct`, `t_` for `typedef`, `u_` for `union`, `e_` for `enum`, `g_` for globals.
- Globals: disallowed unless project permits; if used, they must be `const` or `static` and named with `g_`.
- File/dir names: lowercase `snake_case` only.
- Names must be explicit, readable English; avoid cryptic abbreviations.
- The code must compile.

Examples

Correct:
```c
struct s_point { int x; int y; };
typedef struct s_point t_point;
static int g_counter;
int do_work(void);
```

Incorrect:
```c
struct Point { int x; int y; };      // CamelCase
typedef struct s_point Point;        // Missing t_
int GlobalCounter;                   // Global without g_ and not static/const
int DoWork();                        // Capital letters
```

---

## Formatting

- Indentation: real tabs (ASCII 9), visually 4 spaces per tab.
- Max 80 columns per line (comments included).
- Functions separated by exactly one empty line (no double empty lines anywhere).
- Braces on their own lines, except in type declarations (`struct/union/enum`).
- No trailing spaces; no consecutive spaces.
- Declarations at the beginning of a function; one variable per line. Variable names in a scope align in a column.
- Pointer asterisk sticks to the variable name (not the type).
- No declaration + initialization on the same line inside functions (allowed for globals, `static`, and `const`).
- Only one instruction or control structure per line. No assignments inside control conditions. No multiple assignments per line.
- Long statements may wrap: place the operator at the start of the continued line; indent continuation.
- Spacing: one space after commas/semicolons; exactly one space between operators and operands.
- C keywords are followed by a space, except type keywords (e.g., `int`, `char`, `float`) and `sizeof`.
- Control structures may omit braces only for a single one‑line instruction.

Examples

Correct:
```c
int	my_func(void)
{
	int		count;
	char	*name;

	count = 0;
	name = NULL;
	while (count < 3
		&& name == NULL)
	{
		count = count + 1;
	}
	return (count);
}
```

Incorrect:
```c
int my_func(void){ int count = 0; while((count = f()) && ++count){}} // inline, init+decl, assignment in condition
int* p;   // star attached to type, not variable
int  a, b; // multiple declarations per line
if (x &&
    y) do_something(); // operator at end of previous line
```

Pointer star placement

Correct:
```c
int	*p;
```

Incorrect:
```c
int* p;
```

Declaration vs initialization inside a function

Correct:
```c
int	value;

value = 0;
```

Incorrect:
```c
int value = 0; // not allowed inside function (except static/const)
```

---

## Functions

- Max 25 lines per function (not counting the function’s own braces).
- Max 4 named parameters.
- Prototypes must name parameters.
- Max 5 local variables per function.
- No‑arg functions must use `void`.
- Use exactly one tab between return type and function name.
- Return style: `return (expr);` for non‑void; `return ;` for void.

Examples

Correct:
```c
int	add_two(int a, int b)
{
	int		res;

	res = a + b;
	return (res);
}
```

Incorrect:
```c
int add_two(a, b) // unnamed params in prototype; missing tab; K&R style
{
	return a + b;   // return without parentheses
}
```

---

## Types: typedef, struct, enum, union

- Space after the keyword: `struct s_x`, `enum e_x`, `union u_x`.
- Inside braces, follow normal indentation rules.
- Align structure names in a scope consistently.
- Declare structures in headers, not in `.c` files.
- For `typedef`, add a space after `typedef` and apply normal indentation for the new name.

Examples

Correct (in header):
```c
#ifndef FT_POINT_H
# define FT_POINT_H

typedef struct s_point
{
	int	x;
	int	y;
} t_point;

#endif // FT_POINT_H
```

Incorrect (in a .c file):
```c
struct s_point { int x; int y; }; // struct declared in .c
```

---

## Headers (include files)

- Allowed content only: includes, declarations, `#define`, prototypes, and macros.
- All includes must be at the top of the file.
- Never include a `.c` file anywhere.
- Protect headers with include guards. If the file is `ft_foo.h`, the macro should be `FT_FOO_H`.
- Do not include unused headers (justify inclusion with a comment if needed).

Examples

Correct guard:
```c
#ifndef FT_FOO_H
# define FT_FOO_H

// declarations

#endif // FT_FOO_H
```

Incorrect:
```c
#include "foo.c"    // including a .c file
#include <stdio.h>   // unused include
```

---

## 42 File Header

- Every `.c` and `.h` starts with the standard 42 multi‑line header.
- Keep it up‑to‑date (author login/email, creation date, last update). Configure your editor to auto‑update.

---

## Macros & Preprocessor

- Use `#define` only for literal, constant values.
- Macro names are ALL UPPERCASE.
- No multi‑line macros.
- You may use macros from allowed standard libraries only if the project allows them.
- Indent preprocessor directives inside `#if/#ifdef/#ifndef` blocks.
- Preprocessor directives only at global scope (not inside functions).

Examples

Correct:
```c
#define BUFFER_SIZE 1024
```

Incorrect:
```c
#define add(a,b) a+b       // macro function; not a literal constant
#define LONG(\
  A) 42                   // multiline macro
void f(void) { #define X 1 } // preprocessor inside function
```

---

## Forbidden Constructs

- Not allowed: `for`, `do ... while`, `switch`, `case`, `goto`, ternary `?:`.
- No VLAs (Variable Length Arrays).
- No implicit types in declarations (always provide explicit type).

Examples

Incorrect:
```c
for (int i = 0; i < n; ++i) { /* ... */ }
int n = argc; int a[n]; // VLA
int i; if (a ? b : c) {} // ternary
```

Correct alternatives:
```c
int	i;
	i = 0;
	while (i < n)
	{
		/* ... */
		i = i + 1;
	}
```

---

## Comments

- No comments inside function bodies.
- Comments must be English and useful.
- Allowed placements: end of a line or on their own line (outside function bodies).

Examples

Correct:
```c
// module: parsing utilities
int	parse_input(const char *s);
```

Incorrect:
```c
int	parse_input(const char *s)
{
	// inside-function comment not allowed
	return (0);
}
```

---

## Files

- Do not include a `.c` file in a `.c` file.
- A `.c` file may define at most 5 functions.

---

## Makefile

- Required rules: `$(NAME)`, `all` (default), `clean`, `fclean`, `re`.
- Must not relink when not necessary.
- Multi‑binary: provide a rule per binary; `all` builds all.
- If using a local non‑system library (e.g., `libft`), the Makefile must build it automatically.
- List all source files explicitly; do not use wildcards like `*.c`.

Example (minimal pattern):
```makefile
NAME := myprog
SRCS := src/main.c src/run.c src/util.c
OBJS := $(SRCS:.c=.o)
CC   := cc
CFLAGS := -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
```

---

## Quick Correct vs Incorrect

Constants

Correct:
```c
#define MAX_RETRIES 3
```

Incorrect:
```c
const mr = 3;       // vague name
#define mr 3        // not uppercase; vague
```

Control flow

Correct:
```c
if (ok)
	return (1);
```

Incorrect:
```c
if (ok) return 1;   // inline; missing parentheses on return
ok ? do_a() : do_b(); // ternary not allowed
```

Spacing & wrapping

Correct:
```c
if (a == 1
	&& b == 2)
{
	return (0);
}
```

Incorrect:
```c
if (a == 1 &&
    b == 2) { return (0); }
```

Global variables

Correct (when project allows globals):
```c
static int g_limit = 10; // static global allowed
```

Incorrect:
```c
int g_limit = 10;  // non-static global (forbidden unless explicitly allowed)
```

---

## Notes for Tooling

- Tabs must be preserved (no conversion to spaces). Configure editors and formatters accordingly.
- Enforce 80‑column limit including comments.
- Count function lines excluding the opening/closing braces.
- Track number of local variables per function (≤ 5).
- Verify header guards and absence of unused includes.
- Flag forbidden constructs and preprocessor location.
