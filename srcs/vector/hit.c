/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:00:00 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/13 12:00:00 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** Casts a ray into the scene and returns the color of the closest hit.
** Returns black if no object is intersected.
*/
t_color	trace_ray(t_scene *scene, t_ray ray)
{
	t_hit		closest_hit;
	t_hit		current_hit;
	t_object	*obj;
	t_color		black;

	black.r = 0;
	black.g = 0;
	black.b = 0;
	closest_hit.t = INFINITY;
	obj = scene->objects;
	while (obj)
	{
		if (intersect(ray, obj, &current_hit)
			&& current_hit.t < closest_hit.t)
			closest_hit = current_hit;
		obj = obj->next;
	}
	if (closest_hit.t == INFINITY)
		return (black);
	return (calculate_lighting(scene, &closest_hit));
}
