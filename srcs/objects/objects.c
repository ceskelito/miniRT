/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:00:00 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/13 12:00:00 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hit_plane(t_ray ray, t_plane pl, t_hit *hit)
{
	double	denom;
	double	t;
	t_vec3	p0l0;

	denom = vec3_dot(pl.normal, ray.dir);
	if (fabs(denom) < EPSILON)
		return (false);
	p0l0 = vec3_sub(pl.point, ray.origin);
	t = vec3_dot(p0l0, pl.normal) / denom;
	if (t < EPSILON)
		return (false);
	hit->t = t;
	hit->phit = vec3_add(ray.origin, vec3_mult(ray.dir, t));
	if (denom > 0)
		hit->nhit = vec3_mult(pl.normal, -1.0);
	else
		hit->nhit = pl.normal;
	hit->color = pl.color;
	return (true);
}

bool	hit_sphere(t_ray ray, t_sphere sp, t_hit *hit)
{
	t_vec3	oc;
	double	abc[3];
	double	disc;
	double	t;

	oc = vec3_sub(ray.origin, sp.center);
	abc[0] = vec3_dot(ray.dir, ray.dir);
	abc[1] = 2.0 * vec3_dot(oc, ray.dir);
	abc[2] = vec3_dot(oc, oc) - pow(sp.diameter / 2.0, 2);
	disc = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (disc < 0)
		return (false);
	t = (-abc[1] - sqrt(disc)) / (2.0 * abc[0]);
	if (t < EPSILON)
		t = (-abc[1] + sqrt(disc)) / (2.0 * abc[0]);
	if (t < EPSILON)
		return (false);
	hit->t = (float)t;
	hit->phit = vec3_add(ray.origin, vec3_mult(ray.dir, t));
	hit->nhit = vec3_normalize(vec3_sub(hit->phit, sp.center));
	hit->color = sp.color;
	return (true);
}

/*
** Fills the hit struct for a triangle and returns true.
** Extracted from hit_triangle to stay within the 25-line limit.
*/
static bool	fill_tr_hit(t_hit *hit, t_triangle tr, t_ray ray, double t)
{
	hit->t = t;
	hit->phit = vec3_add(ray.origin, vec3_mult(ray.dir, t));
	if (vec3_dot(tr.n, ray.dir) > 0)
		hit->nhit = vec3_mult(tr.n, -1.0);
	else
		hit->nhit = tr.n;
	hit->color = tr.color;
	return (true);
}

/*
** Moller-Trumbore ray-triangle intersection.
** Uses precomputed edges and normal from the parser.
** u and v are barycentric coordinates.
*/
bool	hit_triangle(t_ray ray, t_triangle tr, t_hit *hit)
{
	t_vec3	hvec;
	t_vec3	svec;
	t_vec3	qvec;
	double	params[3];
	double	t;

	hvec = vec3_cross(ray.dir, tr.edge[1]);
	params[0] = vec3_dot(tr.edge[0], hvec);
	if (fabs(params[0]) < EPSILON)
		return (false);
	params[0] = 1.0 / params[0];
	svec = vec3_sub(ray.origin, tr.c[0]);
	params[1] = params[0] * vec3_dot(svec, hvec);
	if (params[1] < 0.0 || params[1] > 1.0)
		return (false);
	qvec = vec3_cross(svec, tr.edge[0]);
	params[2] = params[0] * vec3_dot(ray.dir, qvec);
	if (params[2] < 0.0 || params[1] + params[2] > 1.0)
		return (false);
	t = params[0] * vec3_dot(tr.edge[1], qvec);
	if (t < EPSILON)
		return (false);
	return (fill_tr_hit(hit, tr, ray, t));
}
