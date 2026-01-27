/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:30:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/27 17:30:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <stdio.h>

void debug_print_vec3(const char *name, t_vec3 vec) {
	printf("%s: (%.2f, %.2f, %.2f)\n", name, vec.x, vec.y, vec.z);
}

void debug_print_color(const char *name, t_color color) {
	printf("%s: RGB(%d, %d, %d)\n", name, color.r, color.g, color.b);
}

void debug_print_ambient(t_ambient ambient) {
	printf("\n=== AMBIENT LIGHTING ===\n");
	printf("Ratio: %.2f\n", ambient.ratio);
	debug_print_color("Color", ambient.color);
}

void debug_print_camera(t_camera camera) {
	printf("\n=== CAMERA ===\n");
	debug_print_vec3("Position", camera.position);
	debug_print_vec3("Orientation", camera.orientation);
	printf("FOV: %d degrees\n", camera.fov);
}

void debug_print_light(t_light light) {
	printf("\n=== LIGHT ===\n");
	debug_print_vec3("Position", light.position);
	printf("Brightness: %.2f\n", light.brightness);
	debug_print_color("Color", light.color);
}
