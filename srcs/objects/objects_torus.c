/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_torus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 12:00:00 by rceschel          #+#    #+#             */
/*   Updated: 2026/02/23 12:00:00 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** Signed Distance Function (SDF) of a torus.
**
** A torus is defined by two radii:
**   big_r (R) = major radius (distance from center to ring)
**   sml_r (r) = minor radius (tube thickness)
**
** For a point P, distance from torus axis:
**   dist_axis = sqrt(|v|^2 - proj^2), where proj = v · orient
** Torus SDF is:
**   sqrt((dist_axis - R)^2 + proj^2) - r
** Positive outside, negative inside, zero on the surface.
*/
static double	torus_sdf(t_vec3 p, t_torus tor)
{
	t_vec3	v;
	double	proj;
	double	dist_axis;
	double	q[2];

	v = vec3_sub(p, tor.coords);
	proj = vec3_dot(v, tor.orient);
	dist_axis = sqrt(vec3_dot(v, v) - proj * proj);
	q[0] = dist_axis - tor.big_r;
	q[1] = proj;
	return (sqrt(q[0] * q[0] + q[1] * q[1]) - tor.sml_r);
}

/*
** Torus normal at the hit point.
**
** Strategy: find the closest point on the torus center ring
** (the circle of radius R). The normal is the normalized vector
** from that ring point to the hit point.
**
** v_perp is the component of v perpendicular to the torus axis.
** ring_pt = center + normalize(v_perp) * R
** normal = normalize(phit - ring_pt)
*/
static t_vec3	get_torus_normal(t_torus tor, t_vec3 phit)
{
	t_vec3	v;
	t_vec3	v_perp;
	double	proj;
	t_vec3	ring_pt;

	v = vec3_sub(phit, tor.coords);
	proj = vec3_dot(v, tor.orient);
	v_perp = vec3_sub(v, vec3_mult(tor.orient, proj));
	ring_pt = vec3_add(tor.coords,
			vec3_mult(vec3_normalize(v_perp), tor.big_r));
	return (vec3_normalize(vec3_sub(phit, ring_pt)));
}

/*
** Helper: fills hit struct for torus and returns true.
** Kept separate to satisfy the 25-line limit of hit_torus.
*/
static bool	fill_torus_hit(t_hit *hit, t_torus tor, t_vec3 p, double t)
{
	hit->t = t;
	hit->phit = p;
	hit->nhit = get_torus_normal(tor, p);
	hit->color = tor.color;
	return (true);
}

/*
** Ray-torus intersection via Sphere Tracing (ray marching).
**
** Instead of solving the quartic equation (degree 4), we use
** the SDF: each step advances along the ray by the SDF value.
** If SDF becomes ~0, we are on the surface.
**
** Limits: 256 max iterations, max distance 10000 units.
** fabs(dist) handles slight overshoot (dist < 0).
*/
bool	hit_torus(t_ray ray, t_torus tor, t_hit *hit)
{
	double	t;
	double	dist;
	int		i;
	t_vec3	p;

	t = EPSILON;
	i = 0;
	while (i < 256)
	{
		p = vec3_add(ray.origin, vec3_mult(ray.dir, t));
		dist = torus_sdf(p, tor);
		if (fabs(dist) < EPSILON)
			return (fill_torus_hit(hit, tor, p, t));
		t = t + fabs(dist);
		if (t > 10000.0)
			return (false);
		i = i + 1;
	}
	return (false);
}
