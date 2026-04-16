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
#include "legend.h"

static t_sphere	light_marker(t_light light)
{
	t_sphere	s;

	s.center = light.light_point;
	s.diameter = LIGHT_MARKER_DIAMETER;
	s.color = light.color;
	return (s);
}

static t_color	black_color(void)
{
	t_color	c;

	c.r = 0;
	c.g = 0;
	c.b = 0;
	return (c);
}

static void	find_closest(t_scene *scene, t_ray ray,
	t_object **closest, t_hit *hit)
{
	t_hit		cur;
	t_object	*obj;

	hit->t = INFINITY;
	*closest = NULL;
	obj = scene->objects;
	while (obj)
	{
		if (intersect(ray, obj, &cur) && cur.t < hit->t)
		{
			*hit = cur;
			*closest = obj;
		}
		obj = obj->next;
	}
}

t_color	trace_ray(t_scene *scene, t_ray ray)
{
	t_hit		closest_hit;
	t_hit		light_hit;
	t_object	*closest;

	find_closest(scene, ray, &closest, &closest_hit);
	if (scene->focused_right_legend == LIGHTS
		&& hit_sphere(ray, light_marker(scene->light), &light_hit)
		&& light_hit.t < closest_hit.t)
		return (scene->light.color);
	if (closest_hit.t == INFINITY)
		return (black_color());
	if (closest == scene->selected_object)
		return (closest_hit.color);
	return (calculate_lighting(scene, &closest_hit));
}
