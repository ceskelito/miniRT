/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_cone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 12:00:00 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/13 12:00:00 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** Computes coefficients a, b, c of the quadratic equation
** for ray-cone intersection.
** The cone apex is at: center + height * axis
** tan(half_angle) = (diameter/2) / height; cos^2 = h^2/(h^2+r^2) = m
*/
static void	get_co_abc(t_ray ray, t_cone co, double *abc)
{
	t_vec3	w;
	double	m;
	double	r;

	r = co.diameter / 2.0;
	m = (co.height * co.height) / (co.height * co.height + r * r);
	w = vec3_sub(ray.origin, vec3_add(co.center,
				vec3_mult(co.axis, co.height)));
	abc[0] = vec3_dot(ray.dir, co.axis) * vec3_dot(ray.dir, co.axis)
		- m * vec3_dot(ray.dir, ray.dir);
	abc[1] = 2.0 * (vec3_dot(ray.dir, co.axis) * vec3_dot(w, co.axis)
			- m * vec3_dot(ray.dir, w));
	abc[2] = vec3_dot(w, co.axis) * vec3_dot(w, co.axis)
		- m * vec3_dot(w, w);
}

/*
** Cone normal at the hit point.
** grad(F) = 2 * [cos^2(a) * v - (v.A) * A], where v = phit - apex.
*/
static t_vec3	get_cone_normal(t_cone co, t_vec3 phit)
{
	t_vec3	v;
	double	m;
	double	r;

	r = co.diameter / 2.0;
	v = vec3_sub(phit, vec3_add(co.center,
				vec3_mult(co.axis, co.height)));
	m = (co.height * co.height) / (co.height * co.height + r * r);
	return (vec3_normalize(vec3_sub(vec3_mult(v, m),
				vec3_mult(co.axis, vec3_dot(v, co.axis)))));
}

/*
** Tests the lateral surface of the cone.
** Both roots are tried; the height range [-height, 0] from apex is enforced.
*/
static bool	hit_co_body(t_ray ray, t_cone co, t_hit *hit)
{
	double	abc[3];
	double	disc;
	double	t;
	double	h;
	t_vec3	base;

	get_co_abc(ray, co, abc);
	disc = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (disc < 0)
		return (false);
	t = (-abc[1] - sqrt(disc)) / (2.0 * abc[0]);
	if (t < EPSILON)
		t = (-abc[1] + sqrt(disc)) / (2.0 * abc[0]);
	if (t < EPSILON)
		return (false);
	hit->phit = vec3_add(ray.origin, vec3_mult(ray.dir, t));
	base = vec3_add(co.center, vec3_mult(co.axis, co.height));
	h = vec3_dot(vec3_sub(hit->phit, base), co.axis);
	if (h < -co.height || h > 0)
		return (false);
	hit->t = (float)t;
	hit->nhit = get_cone_normal(co, hit->phit);
	hit->color = co.color;
	return (true);
}

/*
** Ray-disc intersection for the cone base cap.
** The base disc is at 'center' with radius diameter/2.
*/
static bool	hit_co_cap(t_ray ray, t_cone co, t_hit *hit)
{
	double	denom;
	double	t;
	t_vec3	diff;

	denom = vec3_dot(ray.dir, co.axis);
	if (fabs(denom) < EPSILON)
		return (false);
	t = vec3_dot(vec3_sub(co.center, ray.origin), co.axis) / denom;
	if (t < EPSILON)
		return (false);
	diff = vec3_sub(vec3_add(ray.origin, vec3_mult(ray.dir, t)), co.center);
	if (vec3_dot(diff, diff) > pow(co.diameter / 2.0, 2))
		return (false);
	hit->t = (float)t;
	hit->phit = vec3_add(ray.origin, vec3_mult(ray.dir, t));
	if (denom > 0)
		hit->nhit = vec3_mult(co.axis, -1.0);
	else
		hit->nhit = co.axis;
	hit->color = co.color;
	return (true);
}

/*
** Full ray-cone intersection: tests the lateral body and the base cap,
** then returns the closest hit.
*/
bool	hit_cone(t_ray ray, t_cone co, t_hit *hit)
{
	t_hit	tmp;
	bool	found;

	found = false;
	hit->t = INFINITY;
	if (hit_co_body(ray, co, &tmp) && tmp.t < hit->t)
	{
		*hit = tmp;
		found = true;
	}
	if (hit_co_cap(ray, co, &tmp) && tmp.t < hit->t)
	{
		*hit = tmp;
		found = true;
	}
	return (found);
}
