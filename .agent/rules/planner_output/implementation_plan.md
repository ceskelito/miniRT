# miniRT Implementation Plan

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

### TASK-06: Lighting Calculations
**Goal:** Implement ambient and diffuse (Lambertian) lighting model.

**Files Impacted:**
- `src/lighting/ambient.c`
- `src/lighting/diffuse.c`
- `src/lighting/lighting_utils.c`

**Technical Reference:**
- Section IV - "You must implement ambient and diffuse lighting"
- Ambient: base lighting so objects are never completely dark
- Diffuse: lighting based on angle between surface normal and light direction

**Implementation Details:**
- Ambient contribution: `ambient_ratio * object_color`
- Diffuse contribution: `light_ratio * max(0, dot(normal, light_dir)) * object_color`
- Combine lighting: `ambient + diffuse`
- Clamp color values to [0, 255]

**Validation:**
- Render sphere with only ambient - should be evenly lit
- Render sphere with light from one side - should have gradient
- Test with light behind object - should only show ambient

---

### TASK-07: Shadow Rays
**Goal:** Cast shadow rays to determine if point is occluded from light source.

**Files Impacted:**
- `src/lighting/shadows.c`

**Technical Reference:**
- Section IV - "hard shadows" requirement
- Cast ray from intersection point toward light
- Check if any object blocks the path

**Implementation Details:**
- `int in_shadow(t_scene scene, t_vec3 point, t_light light)`
- Cast ray from `point + epsilon * normal` (to avoid self-intersection) toward light
- Check all objects for intersection before reaching light
- Return 1 if in shadow, 0 if lit

**Validation:**
- Render scene with object between light and surface - should cast shadow
- Test shadow edges are sharp (hard shadows)
- Verify no self-shadowing artifacts

---

### TASK-08: Main Rendering Loop
**Goal:** Trace rays through all pixels and color them based on intersections.

**Files Impacted:**
- `src/render/render.c`
- `src/render/trace_ray.c`
- `src/render/color_utils.c`

**Technical Reference:**
- Combine all previous modules into rendering pipeline
- For each pixel: generate ray, find closest intersection, calculate color

**Implementation Details:**
- `void render_scene(t_scene scene, t_image *img)`
- For each pixel (x, y):
  - Generate camera ray
  - Find closest object intersection
  - If hit: calculate normal, apply lighting, handle shadows
  - If miss: return background color
  - Set pixel color in image buffer
- Handle multiple objects (choose closest intersection)

**Validation:**
- Render test scene with multiple objects
- Verify closest object appears in front
- Check no visual artifacts or glitches

---

### TASK-09: MiniLibX Integration
**Goal:** Initialize window, display rendered image, handle user input.

**Files Impacted:**
- `src/mlx/mlx_init.c`
- `src/mlx/mlx_hooks.c`
- `src/mlx/mlx_image.c`

**Technical Reference:**
- Section IV - Window management requirements
- ESC key closes window and exits cleanly
- Red X button closes window and exits cleanly

**Implementation Details:**
- Initialize MLX: `mlx_init()`
- Create window: `mlx_new_window(mlx, width, height, "miniRT")`
- Create image buffer: `mlx_new_image(mlx, width, height)`
- Register hooks:
  - `mlx_hook()` for window close event
  - `mlx_key_hook()` for ESC key (keycode 53 or 65307)
- Display image: `mlx_put_image_to_window()`
- Clean exit: free all resources, destroy window, exit(0)

**Validation:**
- Window opens and displays rendered image
- Press ESC - window closes, program exits cleanly (no leaks)
- Click red X - window closes, program exits cleanly (no leaks)
- Run with Valgrind: no memory leaks

---

### TASK-10: Error Handling & Memory Management
**Goal:** Ensure proper error messages and no memory leaks.

**Files Impacted:**
- `src/error/error_handling.c`
- `src/memory/cleanup.c`

**Technical Reference:**
- Section IV - "If any misconfiguration is encountered in the file, the program must exit properly and return 'Error\n' followed by an explicit error message"
- Section II - "All heap-allocated memory must be properly freed when necessary. Memory leaks will not be tolerated"

**Implementation Details:**
- Error function: `void exit_error(char *message)` - prints "Error\n" + message, frees all resources, exits
- Cleanup function: `void cleanup_scene(t_scene *scene)` - frees all allocated objects, lists, buffers
- Register cleanup at appropriate points (after MLX init, after parsing, etc.)
- Use consistent error messages for different error types

**Validation:**
- Test all error cases: missing file, invalid format, out-of-range values
- Each should print "Error\n" + specific message
- Run all error cases through Valgrind - no leaks
- Test normal execution through Valgrind - no leaks

---

### TASK-11: Integration & Testing
**Goal:** End-to-end testing with provided example scenes.

**Files Impacted:**
- `scenes/test_sphere.rt`
- `scenes/test_plane.rt`
- `scenes/test_cylinder.rt`
- `scenes/test_complex.rt`

**Technical Reference:**
- Section IV - Example .rt scene
- Section VI - Example renderings

**Implementation Details:**
- Create test scenes covering:
  - Single sphere with lighting
  - Single plane with lighting
  - Single cylinder with lighting
  - Multiple objects with shadows
  - Edge cases: camera positions, extreme FOV
- Test each scene renders correctly
- Compare output to expected results

**Validation:**
- All test scenes render without errors
- Visual inspection: objects appear correct
- Shadows cast correctly
- Colors match scene file specifications
- No crashes or memory leaks with any scene

---

### TASK-12: Norminette Compliance & Final Checks
**Goal:** Ensure all code passes norminette and meets 42 standards.

**Files Impacted:**
- All `.c` and `.h` files

**Technical Reference:**
- The Norm Version 4 (entire document)

**Implementation Details:**
- Run norminette on all files
- Fix any violations:
  - Line length > 80 columns
  - Function length > 25 lines
  - Too many parameters/variables
  - Incorrect naming conventions
  - Missing/incorrect 42 headers
- Verify Makefile doesn't relink
- Final code review for norm compliance

**Validation:**
- `norminette src/ includes/` - all files pass
- `make` twice in a row - second make does nothing (no relink)
- Code review: all functions follow norm, no forbidden constructs
- Final test: compile, run all test scenes, verify clean exit

## 4. Edge Cases & Safety

### Memory Management Risks:
- **Scene Parsing:** Dynamic allocation for variable number of objects - must track and free all allocated objects
- **String Parsing:** Use safe string functions, check for buffer overflows when parsing scene files
- **MLX Resources:** Must destroy images and windows before exit, even on error paths
- **Memory Leak Patterns:** Always pair `malloc` with `free`, test all error paths with Valgrind

### Mathematical Edge Cases:
- **Division by Zero:** Normalize zero-length vectors, ray-plane parallel cases
- **Floating Point Precision:** Use epsilon (1e-6) for comparisons, avoid exact equality checks
- **Quadratic Discriminant:** Negative discriminant = no intersection (handle gracefully)
- **Self-Intersection:** When casting shadow rays, offset starting point by epsilon * normal to avoid hitting same surface
- **Grazing Angles:** Rays nearly parallel to surfaces may cause numerical instability - validate intersection points

### Scene File Validation:
- **Normalized Vectors:** Camera orientation, plane normals, cylinder axis must have length 1.0 (±epsilon)
- **Color Range:** RGB values must be [0, 255] integers
- **Ratio Range:** Ambient and light ratios must be [0.0, 1.0]
- **FOV Range:** Camera FOV must be [0, 180] degrees
- **Positive Values:** Diameters and heights must be positive
- **Duplicate Elements:** A, C, L can only appear once - track and validate
- **Missing Elements:** Scene must have at least A, C, L to be valid

### Cylinder-Specific Issues:
- **Finite vs Infinite:** Cylinder intersection must check both body and caps
- **Cap Orientation:** Caps are perpendicular to cylinder axis - calculate correctly
- **Height Bounds:** Points must be within [0, height] along axis from center

### Rendering Artifacts:
- **Acne (Self-Shadowing):** Offset shadow ray origin slightly along normal
- **Z-Fighting:** When two objects at same distance, choose consistently (first in list)
- **Color Overflow:** Clamp final RGB values to [0, 255] after lighting calculations
- **Undefined Behavior:** Always check intersection distance > epsilon before considering it valid

### User Input Safety:
- **File Not Found:** Check file opening, print clear error message
- **Invalid Format:** Robust parsing with error checking at each step
- **Large Files:** Consider reasonable limits on scene complexity
- **Malformed Numbers:** Use safe conversion functions (ft_atof), validate results

### Platform Considerations:
- **MLX Differences:** MinilibX may behave differently on Linux vs macOS - test keycodes, window behavior
- **Endianness:** When writing to image buffer, respect system endianness for color values
- **Math Library:** Link with `-lm` flag, use standard math.h functions (sqrt, pow, fabs, etc.)
