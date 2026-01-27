---
trigger: always_on
---

# miniRT Implementation Plan task 01-05

## 1. Context Summary

This implementation plan outlines the development of **miniRT**, a raytracing engine written in C that generates computer-generated images using mathematical formulas. The project must render three basic geometric objects (sphere, plane, cylinder) with proper lighting (ambient and diffuse), shadows, and scene parsing from `.rt` files. The implementation must strictly adhere to the 42 Norm (Version 4) coding standards and use the MiniLibX graphics library.

**Core Requirements:**
- Parse scene description files (`.rt` format)
- Implement ray-sphere, ray-plane, and ray-cylinder intersection algorithms
- Calculate ambient and diffuse lighting with spot brightness and hard shadows
- Render images to a window with proper event handling (ESC key, window close)
- Ensure proper memory management with no leaks
- Compile with `-Wall -Wextra -Werror` flags

## 2. Technical Specs & Constraints

### From `.system/rules.md` and `planner_knowledge/coding_norm.md`:

**Naming Conventions:**
- Structures: prefix `s_` (e.g., `s_ray`, `s_sphere`)
- Typedefs: prefix `t_` (e.g., `t_ray`, `t_sphere`)
- Enums: prefix `e_`
- Unions: prefix `u_`
- Globals: prefix `g_` (only `const static` globals allowed)
- All names in snake_case (lowercase with underscores)

**Code Structure:**
- Maximum 25 lines per function (excluding braces)
- Maximum 80 columns per line
- Maximum 4 parameters per function
- Maximum 5 variables per function
- Maximum 5 function definitions per `.c` file
- Functions separated by one empty line
- One instruction per line

**Forbidden Constructs:**
- `for` loops (use `while` instead)
- `do...while` loops
- `switch/case` statements
- `goto` statements
- Ternary operators (`?:`)
- Variable Length Arrays (VLAs)

**File Organization:**
- Headers must have include guards (e.g., `#ifndef MINIRT_H`)
- No `.c` file inclusions
- Structures cannot be declared in `.c` files
- All includes at the beginning of file
- 42 header required at top of every file

**Memory & Safety:**
- All heap memory must be properly freed
- No memory leaks tolerated
- Functions must not crash (segfault, bus error, double free)
- Return values must be in parentheses

**Makefile Requirements:**
- Rules: `$(NAME)`, `all`, `clean`, `fclean`, `re`, `bonus`
- Must not relink
- Compile with `-Wall -Wextra -Werror`
- If using libft, must compile it automatically

### From `planner_knowledge/minirt.subject.md`:

**Mandatory Features:**
- Three geometric objects: sphere, plane, cylinder
- Handle all intersections and object insides
- Object properties: translation, rotation, sizing (diameter for sphere, diameter+height for cylinder)
- Lighting: ambient lighting + diffuse lighting + hard shadows
- Window management: ESC closes window, clicking red X closes window
- Scene file parsing (`.rt` extension)

**Scene File Format:**
- `A`: Ambient lighting (ratio, RGB color)
- `C`: Camera (position, orientation vector, FOV)
- `L`: Light (position, brightness ratio, RGB color)
- `sp`: Sphere (center, diameter, RGB color)
- `pl`: Plane (point, normal vector, RGB color)
- `cy`: Cylinder (center, axis vector, diameter, height, RGB color)

**Error Handling:**
- Exit properly on misconfiguration
- Print `"Error\n"` followed by explicit error message

**External Functions Allowed:**
- Standard: `open, close, read, write, printf, malloc, free, perror, strerror, exit`
- Math library: all functions (compile with `-lm`)
- MinilibX: all functions
- `gettimeofday()`

## 3. Step-by-Step Execution Roadmap

### TASK-01: Project Structure & Makefile
**Goal:** Set up the basic project structure with proper Makefile and header files.

**Files Impacted:**
- `Makefile`
- `includes/minirt.h`
- `includes/structures.h`
- `includes/constants.h`

**Technical Reference:**
- Section II (Common Instructions) - Makefile requirements
- Section III.11 (The Norm) - Makefile rules

**Implementation Details:**
- Create `includes/` directory for all header files
- Create `src/` directory for source files
- Define basic structures: `t_vec3`, `t_ray`, `t_camera`, `t_light`, `t_scene`
- Define object structures: `t_sphere`, `t_plane`, `t_cylinder`
- Set up Makefile with proper flags and rules
- Add 42 header to all files

**Validation:**
- Run `make` - should compile without errors
- Run `make clean` and `make fclean` - should remove object files and binary
- Run `make re` - should recompile everything
- Check for norminette compliance: all files should pass

---

### TASK-02: Vector Mathematics Module
**Goal:** Implement essential 3D vector operations needed for raytracing.

**Files Impacted:**
- `src/vector/vec_operations.c`
- `src/vector/vec_arithmetic.c`
- `src/vector/vec_utils.c`

**Technical Reference:**
- Mathematical foundations for raytracing (vector operations)
- Section III.3 (Functions) - max 25 lines, 4 parameters, 5 variables

**Implementation Details:**
- Vector addition: `t_vec3 vec_add(t_vec3 a, t_vec3 b)`
- Vector subtraction: `t_vec3 vec_sub(t_vec3 a, t_vec3 b)`
- Scalar multiplication: `t_vec3 vec_scale(t_vec3 v, double scalar)`
- Dot product: `double vec_dot(t_vec3 a, t_vec3 b)`
- Cross product: `t_vec3 vec_cross(t_vec3 a, t_vec3 b)`
- Vector length: `double vec_length(t_vec3 v)`
- Vector normalization: `t_vec3 vec_normalize(t_vec3 v)`

**Validation:**
- Create test program that verifies basic operations
- Test normalization with known vectors
- Test dot product returns correct angles (90° = 0, parallel = ±1)

---

### TASK-03: Scene File Parser
**Goal:** Parse `.rt` scene files and populate scene data structure.

**Files Impacted:**
- `src/parser/parse_scene.c`
- `src/parser/parse_elements.c`
- `src/parser/parse_utils.c`
- `src/parser/validate_scene.c`

**Technical Reference:**
- Section IV (Mandatory part) - Scene description format and parsing rules
- Each element type can be set in any order
- Elements with capital letters can only be declared once

**Implementation Details:**
- Parse ambient lighting: `A 0.2 255,255,255`
- Parse camera: `C -50.0,0,20 0,0,1 70`
- Parse light: `L -40.0,50.0,0.0 0.6 10,0,255`
- Parse sphere: `sp 0.0,0.0,20.6 12.6 10,0,255`
- Parse plane: `pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225`
- Parse cylinder: `cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255`
- Validate: A, C, L declared exactly once
- Validate: numerical ranges (colors 0-255, ratios 0.0-1.0, FOV 0-180)
- Validate: normalized vectors (length = 1.0)

**Validation:**
- Test with valid `.rt` file - should parse successfully
- Test with invalid files (missing elements, duplicates, wrong ranges) - should print `"Error\n"` with message
- Test with malformed numbers - should handle gracefully

---

### TASK-04: Ray-Object Intersection Algorithms
**Goal:** Implement mathematical intersection tests for ray-sphere, ray-plane, ray-cylinder.

**Files Impacted:**
- `src/intersect/intersect_sphere.c`
- `src/intersect/intersect_plane.c`
- `src/intersect/intersect_cylinder.c`
- `src/intersect/intersect_utils.c`

**Technical Reference:**
- Section IV - "All possible intersections and the insides of the objects must be handled correctly"
- Ray-sphere: solve quadratic equation
- Ray-plane: solve linear equation with normal vector
- Ray-cylinder: solve for infinite cylinder then clip by height

**Implementation Details:**
- `double intersect_sphere(t_ray ray, t_sphere sphere)`
- `double intersect_plane(t_ray ray, t_plane plane)`
- `double intersect_cylinder(t_ray ray, t_cylinder cylinder)`
- Return distance to intersection (or -1 if no hit)
- Handle edge cases: ray origin inside object, grazing angles, parallel rays

**Validation:**
- Unit test: ray perpendicular to sphere center hits at correct distance
- Unit test: ray parallel to plane never intersects (returns -1)
- Unit test: ray hits cylinder body vs caps
- Test with visualization: render single objects to verify correct shape

---

### TASK-05: Camera & Ray Generation
**Goal:** Generate rays from camera through each pixel of the viewport.

**Files Impacted:**
- `src/camera/camera_setup.c`
- `src/camera/ray_generation.c`

**Technical Reference:**
- Section IV - Camera element with FOV, position, orientation
- Calculate viewport dimensions based on FOV
- Generate ray for each pixel in image

**Implementation Details:**
- Calculate camera basis vectors (right, up, forward) from orientation
- Calculate viewport width/height from FOV and aspect ratio
- For each pixel (x, y): calculate ray direction through that pixel
- `t_ray generate_ray(t_camera cam, int x, int y, int width, int height)`

**Validation:**
- Test: center pixel ray should align with camera orientation
- Test: corner pixels should be at FOV/2 angle from center
- Visual test: render simple scene, verify camera position/orientation works

---

follow in implementation_plan_part2.md