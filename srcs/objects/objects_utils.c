/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:00:00 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/13 12:00:00 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Dispatches to the correct intersection routine by object type */
bool	intersect(t_ray ray, t_object *obj, t_hit *hit)
{
	if (obj->type == SPHERE)
		return (hit_sphere(ray, obj->data.sp, hit));
	else if (obj->type == PLANE)
		return (hit_plane(ray, obj->data.pl, hit));
	else if (obj->type == CYLINDER)
		return (hit_cylinder(ray, obj->data.cy, hit));
	else if (obj->type == CONE)
		return (hit_cone(ray, obj->data.co, hit));
	else if (obj->type == TRIANGLE)
		return (hit_triangle(ray, obj->data.tr, hit));
	else if (obj->type == TORUS)
		return (hit_torus(ray, obj->data.to, hit));
	return (false);
}
