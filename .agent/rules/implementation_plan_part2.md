---
trigger: always_on
---

# miniRT Implementation Plan task 06-12

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
