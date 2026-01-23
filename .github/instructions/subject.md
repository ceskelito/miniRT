---

name: 'subject'

description: 'The subject for this project. All the goals and limits in wich work on the project'

---

# miniRT — AI-Ready Subject (v9.0)

A concise, implementation-oriented specification derived from the provided miniRT subject. Organized by logical subsystems so an AI agent (or developer) can implement modules incrementally.

## Goals & Scope

- Render a 3D scene using a basic ray tracer in C.
- Mandatory lighting: ambient + diffuse (Lambert). Hard shadows recommended.
- Shapes: plane, sphere, cylinder (finite). Handle intersections and object insides.
- Transforms: translation and rotation for objects, lights, and camera (except spheres and lights cannot be rotated).
- UI: display the image in a window; ESC and the window close button must exit cleanly.
- Input: one `.rt` scene file as the first CLI argument.
- Performance: window management must remain fluid (minimize, refocus, etc.).

## Build & Dependencies

- Language: C (compiled with `cc`).
- Flags: `-Wall -Wextra -Werror` plus `-lm` for the math library and MLX/linker flags.
- Allowed functions: `open`, `close`, `read`, `write`, `printf`, `malloc`, `free`, `perror`, `strerror`, `exit`, all functions from `math.h`, all from MiniLibX, `gettimeofday()`.
- Libft: authorized. If used, copy its sources and its Makefile into `libft/` and build it from the project Makefile.
- Makefile rules: `all` (default), `clean`, `fclean`, `re`, `bonus`, and the final binary `$(NAME)` (`miniRT`). No unnecessary relinking.
- Coding rules: conform to the 42 Norm (see the repo’s `md/norm.md`).

Acceptance

- Running `make` builds `miniRT` without relinking on a second run.
- `./miniRT scenes/example.rt` opens a window and displays the rendered image.

---

## Scene File Format (.rt)

- The file is line-based text; elements can be separated by one or more line breaks.
- Whitespace: one or more spaces allowed between tokens; order of elements is free.
- Capital-letter elements may appear only once: `A` (ambient), `C` (camera), `L` (light). Lowercase objects can appear multiple times.
- On any misconfiguration: print `Error\n` then an explanatory message, free resources, and exit with error.

Elements

- Ambient: `A <ratio> <R,G,B>`
  - `ratio`: `[0.0,1.0]`
  - `R,G,B`: each `[0,255]`
  - Example: `A 0.2 255,255,255`

- Camera: `C <x,y,z> <nx,ny,nz> <FOV>`
  - Position `<x,y,z>`: floats
  - Normalized direction `<nx,ny,nz>`: each in `[-1,1]` and norm ≈ 1
  - `FOV`: degrees `[0,180]`
  - Example: `C -50.0,0.0,20.0 0.0,0.0,1.0 70`

- Light: `L <x,y,z> <ratio> [<R,G,B>]`
  - Position `<x,y,z>`: floats
  - Brightness `ratio`: `[0.0,1.0]`
  - Color `[R,G,B]`: `[0,255]` (unused in mandatory; default white if omitted)
  - Example: `L -40.0,50.0,0.0 0.6 255,255,255`

- Sphere: `sp <x,y,z> <diameter> <R,G,B>`
  - Center `<x,y,z>`: floats
  - `diameter`: float > 0
  - Color `<R,G,B>`: `[0,255]`
  - Example: `sp 0.0,0.0,20.6 12.6 10,0,255`

- Plane: `pl <x,y,z> <nx,ny,nz> <R,G,B>`
  - Point `<x,y,z>`: floats
  - Normal `<nx,ny,nz>`: each in `[-1,1]` and norm ≈ 1
  - Color `<R,G,B>`: `[0,255]`
  - Example: `pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225`

- Cylinder: `cy <x,y,z> <nx,ny,nz> <diameter> <height> <R,G,B>`
  - Center `<x,y,z>`: floats
  - Axis `<nx,ny,nz>`: normalized direction, each in `[-1,1]`
  - `diameter`: float > 0; `height`: float > 0
  - Color `<R,G,B>`: `[0,255]`
  - Example: `cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255`

Validation Rules

- Exactly one `A`, one `C`, one `L` must exist.
- All numeric ranges must be respected.
- Vectors that must be normalized must have norm ≈ 1 (tolerate small epsilon).
- Colors must be integers; clamp or reject out-of-range.
- Reject unknown identifiers and malformed lines.

Error Examples

- Incorrect: `C 0,0,0 0,0,0 60` (zero direction vector)
- Incorrect: `A 1.2 255,255,255` (ratio > 1)
- Incorrect: `sp 0,0,0 -5 255,255,255` (negative diameter)

---

## Parsing Subsystem

Responsibilities

- Read the `.rt` file, tokenize lines, detect element type, parse ordered fields with robust error reporting.
- Tolerate extra spaces and blank lines; ignore trailing comments if supported.
- On first error: print `Error\n<reason>`, free all allocations, and exit failure.

Acceptance

- Valid file yields an in-memory scene with one camera, one light, one ambient, and N objects.
- Invalid file stops parsing early with a clear message and no leaks.

---

## Validation Subsystem

Responsibilities

- Enforce element counts (A,C,L), value ranges, normalization of vectors, and positive dimensions.
- Check FOV bounds and color bounds.
- Validate that finite cylinders respect `diameter > 0` and `height > 0`.

Acceptance

- All constraints enforced with specific error messages (e.g., `invalid FOV: 200`).

---

## Data Model

Core Types

- `t_vec3 { x, y, z }` — float/double vectors
- `t_color { r, g, b }` — integers 0..255
- `t_ray { origin, dir }` — normalized `dir`
- `t_camera { pos, dir, fov }`
- `t_light { pos, ratio, color }`
- `t_ambient { ratio, color }`
- `t_material { color }` — minimal for mandatory
- `t_sphere { center, radius }`
- `t_plane { point, normal }`
- `t_cylinder { center, axis, radius, height }`
- `t_object` — tagged union of sphere/plane/cylinder with material
- `t_scene { ambient, camera, light, objects[], img/w,h }`

Acceptance

- Keeps Norm constraints (names, header placement) and header/structs in headers.

---

## Math Utilities

Responsibilities

- Vector ops: add, sub, dot, cross, scale, length, normalize (with epsilon guard).
- Geometry helpers: project, clamp, reflect (for future), orthonormal basis if needed.
- Angle/FOV conversions and ray generation.

Acceptance

- Unit tests or quick checks confirm normalization and dot/cross identities.

---

## Transformations

Responsibilities

- Translation and rotation application to objects, camera, and lights.
- Constraints: spheres and lights cannot be rotated (spheres unaffected by rotation; lights treated as points).
- Rotation represented via axis-angle or Euler and applied to direction vectors and cylinder/plane axes.

Acceptance

- Applying transforms changes positions/orientations consistently without denormals.

---

## Intersections

Responsibilities

- Ray–Sphere: quadratic; return nearest positive t.
- Ray–Plane: handle parallel rays; return nearest positive t.
- Ray–Cylinder (finite): compute side surface intersection using axis; clamp by height; optionally include caps if required by your interpretation; ensure normals are correct for inside/outside handling.
- Return intersection record: `t`, `point`, `normal`, `material`.

Acceptance

- For a simple known scene, closest hit per pixel is consistent and stable.
- No self-intersections after hit (use small epsilon offsets if needed).

---

## Shading & Lighting

Responsibilities

- Ambient term: `ambient_color = ambient.ratio * ambient.color`.
- Diffuse (Lambert): `max(0, dot(n, L)) * light.ratio * object_color * light_color` (with color channels in linear or sRGB—choose and stay consistent).
- Hard shadows (recommended): cast a shadow ray toward the light; if occluded before reaching it, apply ambient only.
- Clamp color channels to [0,255].

Acceptance

- Objects are never fully black due to ambient.
- Surfaces facing away from the light show zero diffuse.

---

## Rendering Pipeline

Responsibilities

- Create an off-screen image with MiniLibX; per-pixel ray generation based on camera FOV and orientation.
- For each pixel: trace primary ray, find closest hit, shade; or set background color if no hit.
- Push the final image to the window.

Acceptance

- Window shows a stable image; resizing is not required unless you extend it.
- No visible tearing or partial buffers.

---

## Window & Events

Responsibilities

- Initialize MLX, create window, create image buffer, display image.
- Event handling:
  - ESC key closes the window and exits cleanly.
  - Window close button (red cross) closes and exits cleanly.
- Keep UI responsive to window focus/minimize/restore.

Acceptance

- Pressing ESC or clicking the close button leads to a clean shutdown without leaks.

---

## Error Handling & Exit

Requirements

- On any parsing/validation error: print `Error\n` followed by a clear message, free all resources, and exit failure.
- On runtime/resource errors (e.g., MLX/image creation failure): print a clear message, free resources, and exit.
- All heap memory freed on normal and error paths; no leaks.

Example

- `Error\ninvalid ambient ratio: 1.5` then terminate cleanly.

---

## Performance & Limits

- Use simple, robust implementations first; optimize only if necessary.
- Single light and simple shading are acceptable for the mandatory part.
- Avoid per-pixel allocations; reuse buffers; keep small epsilons to stabilize intersection.

---

## Testing Scenes

- Minimal scene (white ambient, one light, one sphere and plane):
```
A 0.2 255,255,255
C 0,0,0 0,0,1 70
L 0,10,10 0.6 255,255,255
sp 0,0,20 10 200,50,50
pl 0,-5,0 0,1,0 100,100,100
```

- Cylinder example:
```
A 0.1 255,255,255
C -30,0,10 1,0,0 60
L 0,0,10 0.5 255,255,255
cy 0,0,30 0,0,1 8 20 50,200,50
```

---

## Bonus Roadmap (Optional)

- Specular reflection (Phong), checkerboard textures, colored/multiple lights, additional objects (cone, paraboloid, etc.), bump mapping, skybox, reflections/refractions. Implement only after the mandatory part is correct and stable.

---

## AI Task Handoffs

Use these tasks to request focused implementations:

- Parsing: implement `.rt` lexer/parser with strict validation and error reporting.
- Validation: enforce counts and ranges; vector normalization checks.
- Math: vector library with tests; robust normalization and epsilon handling.
- Data Model: define headers and types; keep `.h` clean and guarded.
- Intersections: sphere, plane, cylinder (finite) with correct normals.
- Shading: ambient + diffuse; add shadow rays for hard shadows.
- Rendering: camera rays and image generation; MLX image buffer write and display.
- Window/Events: MLX init, window/display, ESC and close handling, cleanup.
- Error Handling: unified error API to print `Error\n<message>` and free resources.
- Makefile: strict targets, flags, `libft` integration (if used), no relinks.

Acceptance Criteria per Task

- Unit or ad-hoc tests demonstrate correct behavior for the module.
- Integration renders the sample scenes without crashes or leaks.

---

## Correct vs Incorrect Examples

Parsing

- Correct: `pl 0,0,-10 0,1,0 0,0,225`
- Incorrect: `pl 0,0,-10 0,0,0 0,0,225` (zero normal)

Camera

- Correct: `C -50,0,20 0,0,1 70`
- Incorrect: `C -50,0,20 0,0,1 200` (FOV > 180)

Colors

- Correct: `10,0,255`
- Incorrect: `10,-1,300` (out of range)

Exit

- Correct: Print `Error\n<reason>` and free all before exiting.

---

## Notes

- Keep strict Norm compliance (tabs, line length, naming). See `md/norm.md`.
- Use off-screen images for drawing; avoid per-pixel MLX calls directly to the window.
- Use `gettimeofday()` for optional benchmarking, not as a core dependency.
