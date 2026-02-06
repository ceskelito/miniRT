/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 11:42:00 by antigravit        #+#    #+#             */
/*   Updated: 2026/02/06 10:54:00 by rceschel         ###   ########.fr       */
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

// Ric -> Rob ??
// Come mai abbiamo la struct colors, se poi ogni elemento mantiene il suo colore nella propria?
typedef struct s_colors
{
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;
	t_color	reflect;
	t_color	refract;
	bool	is_shadow;
}	t_colors;

typedef struct s_hit
{
	t_vec3	nhit;
	t_vec3	phit;
	float	t;
	t_color	color;
}	t_hit;

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
** Main Scene & Context
** --------------------------------------------------------------------------
*/

// Mandatory to avoid recursive inclusion
typedef struct s_object t_object;

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
