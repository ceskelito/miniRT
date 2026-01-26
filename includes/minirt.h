/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 11:42:00 by antigravit        #+#    #+#             */
/*   Updated: 2026/01/26 11:42:00 by antigravit       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

/*
** --------------------------------------------------------------------------
** Macros
** --------------------------------------------------------------------------
*/

# define WIDTH 1920
# define HEIGHT 1080
# define EPSILON 0.00001

/*
** --------------------------------------------------------------------------
** Basic Structures
** --------------------------------------------------------------------------
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
** --------------------------------------------------------------------------
** Ray Structure
** --------------------------------------------------------------------------
*/

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}	t_ray;

/*
** --------------------------------------------------------------------------
** Scene Elements
** --------------------------------------------------------------------------
*/

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_camera
{
	t_vec3	view_point;
	t_vec3	orientation;
	double	fov;
}	t_camera;

typedef struct s_light
{
	t_vec3	light_point;
	double	brightness_ratio;
	t_color	color;
}	t_light;

/*
** --------------------------------------------------------------------------
** Shapes
** --------------------------------------------------------------------------
*/

typedef struct s_sphere
{
	double	diameter;
	t_vec3	center;
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
	double	diameter;
	double	height;
	t_vec3	center;
	t_vec3	axis;
	t_color	color;
}	t_cylinder;

/*
** --------------------------------------------------------------------------
** Object Wrapper (Tagged Union)
** --------------------------------------------------------------------------
*/

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_object_type;

typedef union u_object_data
{
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
}	t_object_data;

typedef struct s_object
{
	t_object_type	type;
	t_object_data	data;
	struct s_object	*next;
}	t_object;

/*
** --------------------------------------------------------------------------
** Main Scene & Context
** --------------------------------------------------------------------------
*/

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_object	*objects;
}	t_scene;

typedef struct s_minirt
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	t_scene	scene;
}	t_minirt;

#endif
