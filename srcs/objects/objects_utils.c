/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:00:00 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/14 16:48:58 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

static t_hit	do_ray_hit(t_minirt *rt, t_object *obj, int x, int y)
{
	t_hit	hit;
	int		cs[4];

	cs[0] = x;
	cs[1] = y;
	cs[2] = rt->width;
	cs[3] = rt->height;
	hit.t = INFINITY;
	intersect(camera_ray(rt->scene.camera, cs, cs + 2), obj, &hit);
	return (hit);
}

t_object	*get_selected_object(t_minirt *rt, int x, int y)
{
	t_hit		closest_hit;
	t_hit		cur;
	t_object	*curr;
	t_object	*closest;

	closest_hit.t = INFINITY;
	closest = NULL;
	curr = rt->scene.objects;
	while (curr)
	{
		cur = do_ray_hit(rt, curr, x, y);
		if (cur.t < closest_hit.t)
		{
			closest_hit = cur;
			closest = curr;
		}
		curr = curr->next;
	}
	if (closest_hit.t == INFINITY)
		return (NULL);
	return (closest);
}
