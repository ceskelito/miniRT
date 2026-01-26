# Changelog

All notable changes to the miniRT project will be documented in this file.

## [Unreleased] - 2026-01-26

### Added
- **Parsing Subsystem**: Complete lexer and parser for `.rt` files.
    - Custom `ft_atof` for double precision parsing.
    - Strict validation of element counts and value ranges.
- **Data Structures**: `minirt.h` defining `t_scene`, `t_object`, `t_vec3`, etc.
- **Utils**: `print_scene` debug function in `srcs/utils/debug.c`.
- **Scripts**: `test_parser.py` for automated verification of parser rules.

### Changed
- **Makefile**: Updated to compile parsing sources and link `libft` correctly.
