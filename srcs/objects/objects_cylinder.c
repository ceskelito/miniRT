/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_cylinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:00:00 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/13 12:00:00 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** Computes quadratic coefficients for the infinite cylinder equation.
** abc[0..2] correspond to a, b, c in at^2 + bt + c = 0.
*/
static void	get_cy_abc(t_ray ray, t_cylinder cy, double *abc)
{
	t_vec3	oc;

	oc = vec3_sub(ray.origin, cy.center);
	abc[0] = vec3_dot(ray.dir, ray.dir)
		- pow(vec3_dot(ray.dir, cy.axis), 2);
	abc[1] = 2 * (vec3_dot(ray.dir, oc)
			- (vec3_dot(ray.dir, cy.axis) * vec3_dot(oc, cy.axis)));
	abc[2] = vec3_dot(oc, oc) - pow(vec3_dot(oc, cy.axis), 2)
		- pow(cy.diameter / 2, 2);
}

/*
** Validates a single cylinder root: checks that t is positive and that
** the hit point lies within the finite height of the cylinder.
*/
static bool	cy_check_root(t_ray ray, t_cylinder cy, double t, t_hit *hit)
{
	double	h;

	if (t < EPSILON)
		return (false);
	hit->phit = vec3_add(ray.origin, vec3_mult(ray.dir, t));
	h = vec3_dot(vec3_sub(hit->phit, cy.center), cy.axis);
	if (h < -cy.height / 2.0 || h > cy.height / 2.0)
		return (false);
	hit->t = (float)t;
	hit->nhit = vec3_normalize(vec3_sub(hit->phit,
				vec3_add(cy.center, vec3_mult(cy.axis, h))));
	hit->color = cy.color;
	return (true);
}

/*
** Tests the lateral body of the cylinder, trying both quadratic roots.
*/
static bool	hit_cy_body(t_ray ray, t_cylinder cy, t_hit *hit)
{
	double	abc[3];
	double	disc;
	double	t1;
	double	t2;

	get_cy_abc(ray, cy, abc);
	disc = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (disc < 0)
		return (false);
	t1 = (-abc[1] - sqrt(disc)) / (2.0 * abc[0]);
	t2 = (-abc[1] + sqrt(disc)) / (2.0 * abc[0]);
	if (cy_check_root(ray, cy, t1, hit))
		return (true);
	return (cy_check_root(ray, cy, t2, hit));
}

/*
** Ray-disc intersection for a cylinder cap.
** cap_offset is +height/2 (top cap) or -height/2 (bottom cap).
*/
static bool	hit_cy_cap(t_ray ray, t_cylinder cy, double cap_offset,
				t_hit *hit)
{
	t_vec3	cap_center;
	double	denom;
	double	t;
	t_vec3	diff;

	denom = vec3_dot(ray.dir, cy.axis);
	if (fabs(denom) < EPSILON)
		return (false);
	cap_center = vec3_add(cy.center, vec3_mult(cy.axis, cap_offset));
	t = vec3_dot(vec3_sub(cap_center, ray.origin), cy.axis) / denom;
	if (t < EPSILON)
		return (false);
	diff = vec3_sub(vec3_add(ray.origin, vec3_mult(ray.dir, t)), cap_center);
	if (vec3_dot(diff, diff) > pow(cy.diameter / 2.0, 2))
		return (false);
	hit->t = (float)t;
	hit->phit = vec3_add(ray.origin, vec3_mult(ray.dir, t));
	if (denom > 0)
		hit->nhit = vec3_mult(cy.axis, -1.0);
	else
		hit->nhit = cy.axis;
	hit->color = cy.color;
	return (true);
}

/*
** Full ray-cylinder intersection: tests the lateral body and both caps,
** then returns the closest hit among the three.
*/
bool	hit_cylinder(t_ray ray, t_cylinder cy, t_hit *hit)
{
	t_hit	tmp;
	bool	found;

	found = false;
	hit->t = INFINITY;
	if (hit_cy_body(ray, cy, &tmp) && tmp.t < hit->t)
	{
		*hit = tmp;
		found = true;
	}
	if (hit_cy_cap(ray, cy, cy.height / 2.0, &tmp) && tmp.t < hit->t)
	{
		*hit = tmp;
		found = true;
	}
	if (hit_cy_cap(ray, cy, -cy.height / 2.0, &tmp) && tmp.t < hit->t)
	{
		*hit = tmp;
		found = true;
	}
	return (found);
}
