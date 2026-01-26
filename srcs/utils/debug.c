/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:00:00 by antigravit        #+#    #+#             */
/*   Updated: 2026/01/26 12:00:00 by antigravit       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void print_vec3(char *name, t_vec3 v) {
	printf("  %s: %.2f, %.2f, %.2f\n", name, v.x, v.y, v.z);
}

static void print_color(char *name, t_color c) {
	printf("  %s: %d, %d, %d\n", name, c.r, c.g, c.b);
}

void print_scene(t_minirt *rt) {
	t_object *obj;
	int i;

	printf("=== SCENE DATA ===\n");
	printf("[Ambient]\n");
	printf("  Ratio: %.2f\n", rt->scene.ambient.ratio);
	print_color("Color", rt->scene.ambient.color);
	printf("[Camera]\n");
	print_vec3("View Point", rt->scene.camera.view_point);
	print_vec3("Orientation", rt->scene.camera.orientation);
	printf("  FOV: %.2f\n", rt->scene.camera.fov);
	printf("[Light]\n");
	print_vec3("Point", rt->scene.light.light_point);
	printf("  Brightness: %.2f\n", rt->scene.light.brightness_ratio);
	print_color("Color", rt->scene.light.color);
	printf("[Objects]\n");
	obj = rt->scene.objects;
	i = 0;
	while (obj) {
		printf("  Object %d: ", i++);
		if (obj->type == SPHERE) {
			printf("SPHERE\n");
			print_vec3("    Center", obj->data.sp.center);
			printf("    Diameter: %.2f\n", obj->data.sp.diameter);
			print_color("    Color", obj->data.sp.color);
		} else if (obj->type == PLANE) {
			printf("PLANE\n");
			print_vec3("    Point", obj->data.pl.point);
			print_vec3("    Normal", obj->data.pl.normal);
			print_color("    Color", obj->data.pl.color);
		} else if (obj->type == CYLINDER) {
			printf("CYLINDER\n");
			print_vec3("    Center", obj->data.cy.center);
			print_vec3("    Axis", obj->data.cy.axis);
			printf("    Diameter: %.2f\n", obj->data.cy.diameter);
			printf("    Height: %.2f\n", obj->data.cy.height);
			print_color("    Color", obj->data.cy.color);
		}
		obj = obj->next;
	}
	printf("==================\n");
}
