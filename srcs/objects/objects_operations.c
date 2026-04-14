/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:32:03 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/14 16:39:22 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

static t_vec3	vec3_rotate(t_vec3 v, char axis, double rad)
{
	double	c;
	double	s;
	t_vec3	r;

	c = cos(rad);
	s = sin(rad);
	r = v;
	if (axis == 'x')
	{
		r.y = v.y * c - v.z * s;
		r.z = v.y * s + v.z * c;
	}
	else if (axis == 'y')
	{
		r.x = v.x * c + v.z * s;
		r.z = -v.x * s + v.z * c;
	}
	else if (axis == 'z')
	{
		r.x = v.x * c - v.y * s;
		r.y = v.x * s + v.y * c;
	}
	return (r);
}

static void	rotate_vec3(t_vec3 *v, char axis, int rotate_value)
{
	double	rad;

	rad = rotate_value * (M_PI / 180.0);
	*v = vec3_normalize(vec3_rotate(*v, axis, rad));
}

int	object_rotate(t_object *selected, char axis, int rotate_value)
{
	if (selected->type == CYLINDER)
		rotate_vec3(&selected->data.cy.axis, axis, rotate_value);
	else if (selected->type == CONE)
		rotate_vec3(&selected->data.co.axis, axis, rotate_value);
	else if (selected->type == TORUS)
		rotate_vec3(&selected->data.to.orient, axis, rotate_value);
	else if (selected->type == PLANE)
		rotate_vec3(&selected->data.pl.normal, axis, rotate_value);
	else
		return (0);
	return (1);
}

int	object_resize(t_object *selected, int resize_value)
{
	if (selected->type == SPHERE)
		selected->data.sp.diameter += resize_value;
	else if (selected->type == CYLINDER)
	{
		selected->data.cy.diameter += resize_value;
		selected->data.cy.height += resize_value;
	}
	else if (selected->type == TORUS)
	{
		selected->data.to.sml_r += ((float)resize_value / 2);
		selected->data.to.sml_r2 += pow(selected->data.to.sml_r, 2);
		selected->data.to.big_r += resize_value;
		selected->data.to.big_r2 += pow(selected->data.to.big_r, 2);
	}
	else
		return (0);
	return (1);
}

int	resize_object(t_object *selected, int resize_value)
{
	return (object_resize(selected, resize_value));
}

int	rotate_object(t_object *selected, char axis, int rotate_value)
{
	return (object_rotate(selected, axis, rotate_value));
}
