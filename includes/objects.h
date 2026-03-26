/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 11:42:00 by antigravit        #+#    #+#             */
/*   Updated: 2026/02/18 15:23:21 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "vec3.h"

typedef struct s_color
{
	int					r;
	int					g;
	int					b;
} t_color;

/*
** --------------------------------------------------------------------------
** Shapes
** --------------------------------------------------------------------------
*/

typedef struct s_sphere
{
	double			diameter;
	t_vec3			center;
	t_color			color;
}					t_sphere;

typedef struct s_plane
{
	t_vec3			point;
	t_vec3			normal;
	t_color			color;
}					t_plane;

typedef struct s_cylinder
{
	double			diameter;
	double			height;
	t_vec3			center;
	t_vec3			axis;
	t_color			color;
}					t_cylinder;

typedef struct s_triangle
{
	t_vec3			c[3];
	t_vec3			edge[3];
	t_vec3			n;
	t_color			color;
	float			area2;
}					t_triangle;

typedef struct s_cone
{
	double			diameter;
	double			height;
	t_vec3			center;
	t_vec3			axis;
	t_color			color;
}					t_cone;

typedef struct s_torus
{
	t_vec3			coords;
	t_vec3			orient;
	float			sml_r;
	float			sml_r2;
	float			big_r;
	float			big_r2;
	t_color			color;
}					t_torus;

/*
** --------------------------------------------------------------------------
** Object Wrapper (Tagged Union)
** --------------------------------------------------------------------------
*/

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
	TRIANGLE,
	TORUS
}					t_object_type;

typedef union u_object_data
{
	t_sphere		sp;
	t_plane			pl;
	t_cylinder		cy;
	t_cone			co;
	t_triangle		tr;
	t_torus			to;
}					t_object_data;

typedef struct s_object
{
	t_object_type	type;
	t_object_data	data;
	struct s_object	*next;
}					t_object;

#endif
