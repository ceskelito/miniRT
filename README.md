# miniRT

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
