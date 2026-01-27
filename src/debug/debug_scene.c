/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:30:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/27 17:30:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <stdio.h>

static void debug_print_object(t_object *obj) {
	if (obj->type == OBJ_SPHERE)
		debug_print_sphere(*(t_sphere *)obj->data);
	else if (obj->type == OBJ_PLANE)
		debug_print_plane(*(t_plane *)obj->data);
	else if (obj->type == OBJ_CYLINDER)
		debug_print_cylinder(*(t_cylinder *)obj->data);
}

void debug_print_scene(t_scene scene) {
	t_object *current;
	int count;

	printf("\n");
	printf("╔══════════════════════════════════════════════╗\n");
	printf("║         MINIRT SCENE DEBUG OUTPUT            ║\n");
	printf("╚══════════════════════════════════════════════╝\n");
	debug_print_ambient(scene.ambient);
	debug_print_camera(scene.camera);
	debug_print_light(scene.light);
	printf("\n=== OBJECTS ===\n");
	current = scene.objects;
	count = 0;
	while (current) {
		count++;
		debug_print_object(current);
		current = current->next;
	}
	printf("\nTotal objects: %d\n", count);
	printf("\n");
	printf("══════════════════════════════════════════════\n");
}
