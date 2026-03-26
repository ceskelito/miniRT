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
** Signed Distance Function (SDF) del toro.
**
** Un toro e' definito da due raggi:
**   big_r (R) = raggio maggiore (distanza dal centro all'anello)
**   sml_r (r) = raggio minore (spessore del tubo)
**
** Per un punto P, distanza dall'asse del toro:
**   dist_axis = sqrt(|v|^2 - proj^2), con proj = v · orient
** La SDF del toro e':
**   sqrt((dist_axis - R)^2 + proj^2) - r
** Positiva fuori, negativa dentro, zero sulla superficie.
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
** Normale del toro nel punto di impatto.
**
** Strategia: trovare il punto piu' vicino sull'anello centrale
** del toro (il cerchio di raggio R). La normale e' il vettore
** che va da quel punto al punto di impatto, normalizzato.
**
** v_perp e' la componente di v perpendicolare all'asse del toro.
** ring_pt = centro + normalize(v_perp) * R
** normale = normalize(phit - ring_pt)
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
** Helper: riempie la struct hit per il toro e restituisce true.
** Separata per rispettare il limite di 25 righe di hit_torus.
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
** Intersezione raggio-toro tramite Sphere Tracing (ray marching).
**
** Invece di risolvere l'equazione quartica (grado 4), usiamo
** la SDF: ad ogni passo avanziamo lungo il raggio di una distanza
** pari alla SDF stessa. Se la SDF diventa ~0, siamo sulla superficie.
**
** Limiti: 256 iterazioni massime, distanza massima 10000 unita'.
** fabs(dist) gestisce il caso di leggero overshoot (dist < 0).
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
