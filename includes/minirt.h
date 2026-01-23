/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:00:00 by rceschel          #+#    #+#             */
/*   Updated: 2026/01/23 14:47:38 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdbool.h>
# include <stddef.h>
# include "libft.h"

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_ambient
{
	double	intensity;
	t_color	color;
	bool	present;
}	t_ambient;

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	dir;
	double	fov;
}	t_camera;

typedef struct s_light
{
	t_vec3	pos;
	double	intensity;
	t_color	color;
}	t_light;

typedef struct s_sphere
{
	t_vec3	center;
	double	diameter;
	t_color	color;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	point;
	t_vec3	normal;
	t_color	color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3	pos;
	t_vec3	axis;
	double	diameter;
	double	height;
	t_color	color;
}	t_cylinder;

typedef enum e_token
{
	TOK_EMPTY,
	TOK_AMBIENT,
	TOK_CAMERA,
	TOK_LIGHT,
	TOK_SPHERE,
	TOK_PLANE,
	TOK_CYLINDER,
	TOK_UNKNOWN
}	t_token;

typedef enum e_parse_error
{
	PARSE_OK = 0,
	PARSE_ERR_IO,
	PARSE_ERR_SYNTAX,
	PARSE_ERR_RANGE,
	PARSE_ERR_DUPLICATE,
	PARSE_ERR_MEM,
	PARSE_ERR_UNSUPPORTED
}	t_parse_error;

typedef struct s_scene
{
	t_ambient	ambient;
	t_list		*cameras;
	t_list		*lights;
	t_list		*spheres;
	t_list		*planes;
	t_list		*cylinders;
}	t_scene;

typedef struct s_parse_state
{
	const char	*path;
	size_t		line;
	t_scene		*scene;
}	t_parse_state;

/* Initialize a scene container before parsing. */
void			scene_init(t_scene *scene);

/* Release all heap data stored inside a scene. */
void			scene_clear(t_scene *scene);

/* Parse a .rt file and fill the given scene. */
t_parse_error	parse_scene(const char *path, t_scene *scene);

/* Parse a floating point number with full validation. */
int				parse_double(const char *str, double *out);

/* Parse a vector in the form "x,y,z". */
int				parse_vec3(const char *token, t_vec3 *out);

/* Parse a color in the form "r,g,b". */
int				parse_color(const char *token, t_color *out);

/* Release a NULL-terminated split array. */
void			free_split(char **parts);

/* Print parsed scene data to stdout for debugging. */
void			debug_print_scene(const t_scene *scene);

#endif