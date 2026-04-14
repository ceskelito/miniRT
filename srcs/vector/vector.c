/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:00:00 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/13 12:00:00 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

t_vec3	vec3_mult(t_vec3 a, double scalar)
{
	t_vec3	res;

	res.x = a.x * scalar;
	res.y = a.y * scalar;
	res.z = a.z * scalar;
	return (res);
}

/* Scalar (dot) product of two vectors */
double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec3_normalize(t_vec3 a)
{
	double	len;
	t_vec3	zero;

	zero.x = 0;
	zero.y = 0;
	zero.z = 0;
	len = vec3_length(a);
	if (len == 0)
		return (zero);
	return (vec3_mult(a, 1.0 / len));
}
