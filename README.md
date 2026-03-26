# miniRT

_This project has been created as part
of the 42 curriculum by rceschel, rponticiello_

## Description

**MiniRT** stands for 'Mini Ray Tracer' - and this is what we'll do in this project.

The **Ray Tracing** is a mathematical model to emulate the light refraction in the most realistic way possible.
In order to implement a Ray Tracer we will first of all write a 3D renderer to render the scene and objects.
The graphic library used in this project is MinilibX, wrote from 42ecole for study pourposes.

## Instructions

To compile the project simply type `make` in the root of the repository. The makefile will recursively compile every external library.
**Make sure that you have pulled the libft and MinilibX subrepos**.
To propagate the *clean*, *fclean* and *re* command simply prefix *deep* to the rule name. In example, to recompile the whole project: `make deepre`.

## Resources


//////////////////////////////////////////////////////////////////////////////

A minimal Ray Tracer implemented in C as part of the 42 Common Core curriculum.

## Features

- **Parsing**: Strict validation of `.rt` scene files.
- **Data Structures**: Efficient storage using tagged unions for objects (Sphere, Plane, Cylinder).
- **Elements**: Supports Ambient Light, Camera, and Point Lights.
- **Validation**: Enforces numeric ranges (FOV, Colors, Ratios) and element counts.

## Usage

### Build
```bash
make
```

### Run
```bash
./minirt scenes/example.rt
```

### Verification
Run the automated test script to check parser validity:
```bash
./test_parser.py
```

## Documentation

- [Technical Overview](docs/technical_overview.md): Details on architecture, data structures, and implementation.
- [Changelog](CHANGELOG.md): History of changes.
