/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 11:42:00 by antigravit        #+#    #+#             */
/*   Updated: 2026/04/10 11:39:19 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <errno.h>
# include <string.h> // strerror

# include "vec3.h"
# include "objects.h" // defines t_color

typedef struct s_color t_color; // defined in includes/objets.h

// Mandatory to avoid recursive inclusion
typedef struct s_object	t_object;

/*
** --------------------------------------------------------------------------
** Macros
** --------------------------------------------------------------------------
*/

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WIN_NAME "MiniRT"
# define EPSILON 0.00001

/*
* --------------------------------------------------------------------------
** Basic Structures
** --------------------------------------------------------------------------
*/

// Ric -> Rob ??
// Come mai abbiamo la struct colors,
// se poi ogni elemento mantiene il suo colore nella propria?
typedef struct s_colors
{
	t_color				ambient;
	t_color				diffuse;
	t_color				specular;
	t_color				reflect;
	t_color				refract;
	bool				is_shadow;
}						t_colors;

typedef struct s_hit
{
	t_vec3				nhit;
	t_vec3				phit;
	float				t;
	t_color				color;
}						t_hit;

/*
** --------------------------------------------------------------------------
** Ray Structure
** --------------------------------------------------------------------------
*/

typedef struct s_ray
{
	t_vec3				origin;
	t_vec3				dir;
}						t_ray;

/*
** --------------------------------------------------------------------------
** Scene Elements
** --------------------------------------------------------------------------
*/

typedef struct s_ambient
{
	double				ratio;
	t_color				color;
}						t_ambient;

typedef struct s_camera
{
	t_vec3				view_point;
	t_vec3				orientation;
	double				fov;
}						t_camera;

typedef struct s_light
{
	t_vec3				light_point;
	double				brightness_ratio;
	t_color				color;
}						t_light;

/*
** --------------------------------------------------------------------------
** Main Scene & Context
** --------------------------------------------------------------------------
*/

typedef struct s_scene
{
	t_ambient			ambient;
	t_camera			camera;
	t_light				light;
	t_object			*objects;
	t_object			*selected_object;
}						t_scene;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
}				t_mlx;

typedef struct s_minirt
{
	t_mlx		mlx;
	int			width;
	int			height;
	t_scene		scene;
}						t_minirt;

/*
** --------------------------------------------------------------------------
** Function Prototypes
** --------------------------------------------------------------------------
*/

/* srcs/vector/hit.c */
t_color	trace_ray(t_scene *scene, t_ray ray);

/* srcs/objects/objects.c */
bool	hit_sphere(t_ray ray, t_sphere sp, t_hit *hit);
bool	hit_plane(t_ray ray, t_plane pl, t_hit *hit);
bool	hit_cylinder(t_ray ray, t_cylinder cy, t_hit *hit);
bool	hit_triangle(t_ray ray, t_triangle tr, t_hit *hit);

/* srcs/objects/objects_utils.c */
bool		intersect(t_ray ray, t_object *obj, t_hit *hit);
t_object	*get_selected_object(t_minirt *rt, int x, int y);
int			resize_object(t_object *selected, int resize_value);

/* srcs/objects/objects_cone.c */
bool	hit_cone(t_ray ray, t_cone co, t_hit *hit);

/* srcs/objects/objects_torus.c */
bool	hit_torus(t_ray ray, t_torus tor, t_hit *hit);

/* srcs/color/color.c */
t_color	calculate_lighting(t_scene *scene, t_hit *hit);
bool	is_in_shadow(t_scene *scene, t_vec3 point, t_vec3 light_dir);
t_color	color_mult_ratio(t_color obj_c, t_color light_c, double ratio);
t_color	color_add(t_color a, t_color b);

/* srcs/mlx/render.c */
void	render(t_minirt *rt);
t_ray	camera_ray(t_camera cam, int px, int py, int w, int h);

/* srcs/mlx/init.c */
int		mlx_loop_init(t_minirt *rt);
int		rt_close_program(t_minirt *rt);

#endif
