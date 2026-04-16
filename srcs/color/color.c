/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:00:00 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/16 12:00:00 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	color_mult_ratio(t_color obj_c, t_color light_c, double ratio)
{
	t_color	res;

	res.r = (int)((obj_c.r * (light_c.r / 255.0)) * ratio);
	res.g = (int)((obj_c.g * (light_c.g / 255.0)) * ratio);
	res.b = (int)((obj_c.b * (light_c.b / 255.0)) * ratio);
	return (res);
}

t_color	color_add(t_color a, t_color b)
{
	t_color	res;

	if (a.r + b.r > 255)
		res.r = 255;
	else
		res.r = a.r + b.r;
	if (a.g + b.g > 255)
		res.g = 255;
	else
		res.g = a.g + b.g;
	if (a.b + b.b > 255)
		res.b = 255;
	else
		res.b = a.b + b.b;
	return (res);
}

bool	is_in_shadow(t_scene *scene, t_vec3 point, t_vec3 light_dir)
{
	t_ray		shadow_ray;
	t_hit		hit;
	t_object	*obj;
	double		dist_to_light;

	shadow_ray.origin = vec3_add(point, vec3_mult(light_dir, EPSILON));
	shadow_ray.dir = light_dir;
	dist_to_light = vec3_length(vec3_sub(scene->light.light_point, point));
	obj = scene->objects;
	while (obj)
	{
		if (intersect(shadow_ray, obj, &hit))
		{
			if (hit.t > 0 && hit.t < dist_to_light)
				return (true);
		}
		obj = obj->next;
	}
	return (false);
}

static t_color	apply_diffuse(t_scene *scene, t_hit *hit,
	t_color ambient, t_vec3 light_dir)
{
	t_color	diffuse;
	double	dot;
	double	intensity;

	dot = vec3_dot(hit->nhit, light_dir);
	if (dot <= 0)
		return (ambient);
	intensity = dot * scene->light.brightness_ratio;
	diffuse = color_mult_ratio(hit->color, scene->light.color, intensity);
	return (color_add(ambient, diffuse));
}

t_color	calculate_lighting(t_scene *scene, t_hit *hit)
{
	t_color	ambient;
	t_vec3	light_dir;

	ambient = color_mult_ratio(hit->color, scene->ambient.color,
			scene->ambient.ratio);
	light_dir = vec3_normalize(vec3_sub(scene->light.light_point, hit->phit));
	if (is_in_shadow(scene, hit->phit, light_dir))
		return (ambient);
	return (apply_diffuse(scene, hit, ambient, light_dir));
}
