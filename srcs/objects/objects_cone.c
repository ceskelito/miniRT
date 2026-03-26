/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_cone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 12:00:00 by rceschel          #+#    #+#             */
/*   Updated: 2026/02/23 12:00:00 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** Calcolo dei coefficienti a, b, c dell'equazione quadratica
** per l'intersezione raggio-cono.
**
** Il cono ha vertice (apice) in: center + height * axis
** Il semiangolo alpha soddisfa: tan(a) = (diameter/2) / height
** cos^2(a) = h^2 / (h^2 + r^2), chiamato 'm' nel codice.
**
** Equazione implicita del cono dal vertice V con asse A:
**   (P-V)·A)^2 = cos^2(a) * |P-V|^2
**
** Sostituendo P = O + tD e ponendo W = O - V:
**   a = (D·A)^2 - m * (D·D)
**   b = 2 * [(D·A)(W·A) - m * (D·W)]
**   c = (W·A)^2 - m * (W·W)
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
** Normale del cono nel punto di impatto.
**
** Data la superficie implicita F = (v·A)^2 - cos^2(a) * |v|^2 = 0
** il gradiente (normale non normalizzata) e':
**   grad(F) = 2 * [cos^2(a) * v - (v·A) * A]
**
** Questo punta verso l'esterno del cono.
** v = phit - apex (vettore dal vertice al punto di impatto)
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
** Intersezione raggio-cono finito.
**
** Passi:
** 1. Calcola i coefficienti quadratici (get_co_abc)
** 2. Risolvi at^2 + bt + c = 0 con il discriminante
** 3. Prendi la radice piu' piccola positiva (la piu' vicina)
** 4. Verifica che il punto di impatto sia entro l'altezza del cono:
**    la proiezione 'h' dall'apice lungo l'asse deve essere
**    in [-height, 0] (il cono si estende dall'apice verso la base)
*/
bool	hit_cone(t_ray ray, t_cone co, t_hit *hit)
{
	double	abc[3];
	double	disc;
	double	t;
	double	h;

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
	h = vec3_dot(vec3_sub(hit->phit, vec3_add(co.center,
					vec3_mult(co.axis, co.height))), co.axis);
	if (h < -co.height || h > 0)
		return (false);
	hit->t = (float)t;
	hit->nhit = get_cone_normal(co, hit->phit);
	hit->color = co.color;
	return (true);
}
