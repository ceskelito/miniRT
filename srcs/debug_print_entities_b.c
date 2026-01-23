/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_entities_b.c                           :+:      :+:    :+:   */
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
extern void	debug_print_vec3(const char *label, t_vec3 v);

/* Print a labeled RGB color. */
extern void	debug_print_color(const char *label, t_color c);

/* Print cylinder data for one list entry. */
void	debug_print_cylinder(void *content)
{
	t_cylinder	*cyl;

	cyl = (t_cylinder *)content;
	if (cyl == NULL)
		return ;
	debug_print_vec3("    position", cyl->pos);
	debug_print_vec3("    axis", cyl->axis);
	printf("    diameter: %.3f\n", cyl->diameter);
	printf("    height: %.3f\n", cyl->height);
	debug_print_color("    color", cyl->color);
}
