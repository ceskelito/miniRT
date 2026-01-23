/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:00:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/23 00:00:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

/* Print a labeled vector with fixed precision. */
void	debug_print_vec3(const char *label, t_vec3 v)
{
	printf("%s: %.3f, %.3f, %.3f\n", label, v.x, v.y, v.z);
}

/* Print a labeled RGB color. */
void	debug_print_color(const char *label, t_color c)
{
	printf("%s: %d,%d,%d\n", label, c.r, c.g, c.b);
}
