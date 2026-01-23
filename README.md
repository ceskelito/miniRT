# miniRT
This is a project from 42 Roma Common Core. The goal of the project is to
create a renderer with the Ray Tracing algorithm. Written in C, following the
42 Norme.

## Parsing debug run

The current entry point parses a .rt scene file and prints the parsed content
to stdout for debugging.

### Build

```sh
make
```

### Run

```sh
./minirt scenes/placeholder.rt
```

### Supported scene elements

- Ambient light: `A ratio R,G,B`
- Camera: `C x,y,z nx,ny,nz fov`
- Light: `L x,y,z ratio R,G,B`
- Sphere: `sp x,y,z diameter R,G,B`
- Plane: `pl x,y,z nx,ny,nz R,G,B`
- Cylinder: `cy x,y,z nx,ny,nz diameter height R,G,B`
