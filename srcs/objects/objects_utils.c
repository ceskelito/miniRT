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

/*
 * Returns a pointer to the object selected from mouse click.
 * Returns NULL in case of no object (or plane) selected.
 * */
t_object *get_selected_object(t_minirt *rt, int x, int y)
{
    t_hit		closest_hit;
    t_hit		current_hit;
    t_object	*curr;
	t_object	*closest;
	t_ray		ray;

    closest_hit.t = INFINITY; // Start from infinity
    curr = rt->scene.objects;

    while (curr)
    {
		ray = camera_ray(rt->scene.camera, x, y, rt->width, rt->height);
        if (intersect(ray, curr, &current_hit)) // Intersection dispatcher by currect type
        {
            if (current_hit.t < closest_hit.t)
			{
                closest_hit = current_hit;
				closest = curr;
			}
        }
        curr = curr->next;
    }
    if (closest_hit.t == INFINITY || closest->type == PLANE)
		return (NULL);
	return (closest);
}

int resize_object(t_object *selected, int resize_value)
{
	if (selected->type == SPHERE)
		selected->data.sp.diameter += resize_value;
	else if (selected->type == CYLINDER)
	{
		selected->data.cy.diameter += resize_value;
		selected->data.cy.height += resize_value;
	}
	else
		return (0);
	return (1);
}
