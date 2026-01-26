# Technical Overview

## Architecture

The project is structured into modular subsystems:

1.  **Parsing (`srcs/parsing/`)**: Reads and validates input.
2.  **Data Model (`includes/minirt.h`)**: Defines the scene graph.
3.  **Utils (`srcs/utils/`)**: Debugging and cleanup.

## Implementation Details

### Data Structures

We use a **Tagged Union** approach for scene objects to allow a single linked list to store heterogeneous shapes (Sphere, Plane, Cylinder).

```c
typedef enum e_object_type { SPHERE, PLANE, CYLINDER } t_object_type;

typedef struct s_object {
    t_object_type type;
    union {
        t_sphere sp;
        t_plane pl;
        t_cylinder cy;
    } data;
    struct s_object *next;
} t_object;
```

This simplifies the rendering loop: we can iterate over one `objects` list and dispatch intersection tests based on `type`.

### Parsing Strategy

The parsing logic is strict, as required by the subject:

1.  **Read**: `get_next_line` reads the file line-by-line.
2.  **Tokenize**: `ft_split` breaks lines into tokens by spaces.
3.  **Dispatch**: The first token (`A`, `C`, `pl`, etc.) determines the parser function.
4.  **Validate**:
    - **`ft_atof`**: A custom implementation ensures valid float formats.
    - **Ranges**: FOV is checked [0-180], Colors [0-255], Ratios [0.0-1.0].
    - **Counts**: Static counters ensure only one Ambient, Camera, and Light exist.

### Error Handling

Any error (malloc fail, invalid format, out of range) triggers `exit_error`, which:
1.  Prints "Error\n" followed by a specific message.
2.  Calls `free_scene` to release all allocated memory (linked lists, tokens).
3.  Exits with status 1.
