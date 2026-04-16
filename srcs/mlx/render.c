/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 12:00:00 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/16 12:00:00 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "legend.h"
#include "mlx.h"
#include <math.h>

static int	color_to_int(t_color c)
{
	return ((c.r << 16) | (c.g << 8) | c.b);
}

static t_vec3	compute_dir(t_vec3 fwd, t_vec3 right, t_vec3 up, double c[3])
{
	t_vec3	sum;

	sum = vec3_add(vec3_mult(right, c[0] * c[2]), vec3_mult(up, c[1]));
	return (vec3_normalize(vec3_add(fwd, sum)));
}

t_ray	camera_ray(t_camera cam, int pixel[2], int size[2])
{
	t_vec3	fwd;
	t_vec3	up;
	t_vec3	right;
	double	c[3];
	t_ray	ray;

	fwd = vec3_normalize(cam.orientation);
	up = (t_vec3){0, 1, 0};
	if (fabs(vec3_dot(fwd, up)) > 0.999)
		up = (t_vec3){0, 0, 1};
	right = vec3_normalize(vec3_cross(up, fwd));
	up = vec3_cross(fwd, right);
	c[2] = tan((cam.fov / 2.0) * M_PI / 180.0);
	c[0] = (2.0 * (pixel[0] + 0.5) / size[0] - 1.0)
		* ((double)size[0] / (double)size[1]);
	c[1] = (1.0 - 2.0 * (pixel[1] + 0.5) / size[1]) * c[2];
	ray.origin = cam.view_point;
	ray.dir = compute_dir(fwd, right, up, c);
	return (ray);
}

static void	render_rows(t_minirt *rt, char *data, int info[3])
{
	int	pos[2];
	int	size[2];
	int	color;

	size[0] = rt->width;
	size[1] = rt->height;
	pos[1] = 0;
	while (pos[1] < size[1])
	{
		pos[0] = 0;
		while (pos[0] < size[0])
		{
			color = color_to_int(trace_ray(&rt->scene,
						camera_ray(rt->scene.camera, pos, size)));
			*(int *)(data + pos[1] * info[1] + pos[0] * (info[0] / 8)) = color;
			pos[0]++;
		}
		pos[1]++;
	}
}

void	render(t_minirt *rt)
{
	void	*img;
	char	*data;
	int		info[3];

	img = mlx_new_image(rt->mlx.ptr, rt->width, rt->height);
	data = mlx_get_data_addr(img, &info[0], &info[1], &info[2]);
	render_rows(rt, data, info);
	mlx_put_image_to_window(rt->mlx.ptr, rt->mlx.win, img, 0, 0);
	mlx_destroy_image(rt->mlx.ptr, img);
	print_operations_legend(rt);
	print_camera_legend(rt);
}
