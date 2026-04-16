*This project has been created as part of the 42 curriculum by rceschel, rponticiello.*

# miniRT

## Description

`miniRT` is a minimal ray tracer written in C.
Its goal is to render a 3D scene described in a `.rt` file by simulating light rays and computing intersections with geometric objects.

The project focuses on:
- Building a robust scene parser with strict validation.
- Implementing core ray tracing math (vectors, rays, intersections, normals).
- Rendering the result with MinilibX.

Supported scene content includes:
- Ambient light, camera, and point light.
- Sphere, plane, and cylinder objects.

## Instructions

### Prerequisites

- Linux environment with `gcc` and `make`.
- Git submodules initialized (libft and MinilibX):

```bash
git submodule update --init --recursive
```

### Build

```bash
make
```

Useful build targets:

```bash
make debug
make clean
make fclean
make re
make deepre
```

### Run

```bash
./minirt scenes/example.rt
```

Run with Valgrind helper target:

```bash
make run
```

Run with a custom scene:

```bash
make run RT_FILE=scenes/showcase.rt
```

## Resources

Classic references for ray tracing and related topics:

- *Ray Tracing in One Weekend* (Peter Shirley): https://raytracing.github.io/
- Scratchapixel lessons (ray tracing and computer graphics fundamentals): https://www.scratchapixel.com/
- Physically Based Rendering (book and online edition): https://pbr-book.org/
- MinilibX reference and source: [minilibx/README.md](minilibx/README.md)

### AI Usage

AI was used as a support tool for:
- README structure and wording review.
- Minor text polishing and consistency checks.

AI was not used as a replacement for understanding project requirements.
Core implementation decisions and project code ownership remain with the project authors.

## Scene Format (Quick Overview)

Each line in a `.rt` file starts with an identifier:

- `A` for ambient light
- `C` for camera
- `L` for point light
- `sp` for sphere
- `pl` for plane
- `cy` for cylinder

Example scenes are available in the `scenes/` directory.
