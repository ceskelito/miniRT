/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:00:00 by rceschel          #+#    #+#             */
/*   Updated: 2026/01/23 14:11:58 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"

/*
** Basic math / geometry types
*/

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

/*
** Scene elements directly matching .rt entries
*/

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
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
	double	ratio;
	t_color	color;
}	t_light;

/*
** Object types from the subject
*/

typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}	t_obj_type;

typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	point;
	t_vec3	normal;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3	axis;
	double	radius;
	double	height;
}	t_cylinder;

/*
** Generic object container (linked list for easy parsing)
*/

typedef struct s_object
{
	t_obj_type		type;
	t_color			color;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
	}				u;
	struct s_object	*next;
}	t_object;

/*
** Top‑level scene structure used by the parser
*/

typedef struct s_scene
{
	int			has_ambient;
	int			has_camera;
	int			has_light;
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_object	*objects;
}	t_scene;

/*
** Parsing entry point(s) — declarations only, implementation in .c files
*/

int		parse_scene_file(t_scene *scene, const char *path);
void	free_scene(t_scene *scene);

#endif