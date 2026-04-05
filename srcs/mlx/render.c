#include "minirt.h"
#include "mlx.h"
#include <math.h>

/* Converts t_color to the 0x00RRGGBB integer format used by the MLX buffer. */
static int	color_to_int(t_color c)
{
	return ((c.r << 16) | (c.g << 8) | c.b);
}

/*
** Generates a ray from the camera through pixel (px, py).
**
** Camera basis vectors are derived from the orientation vector:
**   right   = normalize(world_up × forward)
**   up      = forward × right   (keeps the basis orthogonal)
** NDC (Normalized Device Coordinates):
**   ndc_x maps [0, width]  → [-1, 1] left to right, scaled by aspect ratio
**   ndc_y maps [0, height] → [ 1,-1] top to bottom (screen Y is inverted)
*/
static t_ray	camera_ray(t_camera cam, int px, int py, int w, int h)
{
	t_vec3	forward;
	t_vec3	world_up;
	t_vec3	right;
	t_vec3	up;
	double	scale;
	double	aspect;
	t_ray	ray;

	forward = vec3_normalize(cam.orientation);
	world_up = (t_vec3){0, 1, 0};
	/* Fallback: if camera looks straight up/down, use Z as world-up */
	if (fabs(vec3_dot(forward, world_up)) > 0.999)
		world_up = (t_vec3){0, 0, 1};
	right = vec3_normalize(vec3_cross(world_up, forward));
	up = vec3_cross(forward, right);
	scale = tan((cam.fov / 2.0) * M_PI / 180.0);
	aspect = (double)w / (double)h;
	ray.origin = cam.view_point;
	ray.dir = vec3_normalize(
		vec3_add(forward,
			vec3_add(
				vec3_mult(right, (2.0 * (px + 0.5) / w - 1.0) * aspect * scale),
				vec3_mult(up, (1.0 - 2.0 * (py + 0.5) / h) * scale)
			)
		)
	);
	return (ray);
}

/*
** Renders the entire scene into an off-screen MLX image buffer,
** then blits it to the window in a single call for efficiency.
** The inner loop casts one ray per pixel and writes the result directly
** into the raw pixel buffer returned by mlx_get_data_addr.
*/
void	render(t_minirt *rt)
{
	void	*img;
	char	*data;
	int		bpp;
	int		line_len;
	int		endian;
	int		px;
	int		py;

	img = mlx_new_image(rt->mlx.ptr, rt->width, rt->height);
	data = mlx_get_data_addr(img, &bpp, &line_len, &endian);
	py = 0;
	while (py < rt->height)
	{
		px = 0;
		while (px < rt->width)
		{
			/* Cast ray, shade, write pixel into the buffer */
			*(int *)(data + py * line_len + px * (bpp / 8)) = color_to_int(
				trace_ray(&rt->scene,
					camera_ray(rt->scene.camera, px, py, rt->width, rt->height))
			);
			px++;
		}
		py++;
	}
	mlx_put_image_to_window(rt->mlx.ptr, rt->mlx.win, img, 0, 0);
	mlx_destroy_image(rt->mlx.ptr, img);
}
