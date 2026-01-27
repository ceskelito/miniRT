/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:30:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/27 17:30:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <stdio.h>

void debug_print_sphere(t_sphere sphere) {
	printf("\n--- SPHERE ---\n");
	debug_print_vec3("Center", sphere.center);
	printf("Diameter: %.2f\n", sphere.diameter);
	debug_print_color("Color", sphere.color);
}

void debug_print_plane(t_plane plane) {
	printf("\n--- PLANE ---\n");
	debug_print_vec3("Point", plane.point);
	debug_print_vec3("Normal", plane.normal);
	debug_print_color("Color", plane.color);
}

void debug_print_cylinder(t_cylinder cylinder) {
	printf("\n--- CYLINDER ---\n");
	debug_print_vec3("Center", cylinder.center);
	debug_print_vec3("Axis", cylinder.axis);
	printf("Diameter: %.2f\n", cylinder.diameter);
	printf("Height: %.2f\n", cylinder.height);
	debug_print_color("Color", cylinder.color);
}
