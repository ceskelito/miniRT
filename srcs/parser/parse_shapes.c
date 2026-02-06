/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:00:00 by antigravit        #+#    #+#             */
/*   Updated: 2026/02/06 11:10:09 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include "parser.h"

static void add_object_to_scene(t_minirt *rt, t_object *new_obj) {
	t_object *curr;

	if (!new_obj)
		exit_error("Memory allocation failed for object", rt);
	if (!rt->scene.objects) {
		rt->scene.objects = new_obj;
	} else {
		curr = rt->scene.objects;
		while (curr->next)
			curr = curr->next;
		curr->next = new_obj;
	}
}

void parse_sphere(char **tokens, t_minirt *rt) {
	t_object *obj;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		exit_error("Invalid Sphere format", rt);
	obj = malloc(sizeof(t_object));
	if (!obj)
		exit_error("Malloc failed", rt);
	obj->type = SPHERE;
	obj->next = NULL;
	if (!parse_vec3(tokens[1], &obj->data.sp.center))
		exit_error("Invalid Sphere center", rt);
	obj->data.sp.diameter = ft_atof(tokens[2]);
	if (!parse_color(tokens[3], &obj->data.sp.color))
		exit_error("Invalid Sphere color", rt);
	add_object_to_scene(rt, obj);
}

void parse_plane(char **tokens, t_minirt *rt) {
	t_object *obj;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		exit_error("Invalid Plane format", rt);
	obj = malloc(sizeof(t_object));
	if (!obj)
		exit_error("Malloc failed", rt);
	obj->type = PLANE;
	obj->next = NULL;
	if (!parse_vec3(tokens[1], &obj->data.pl.point))
		exit_error("Invalid Plane point", rt);
	if (!parse_vec3(tokens[2], &obj->data.pl.normal))
		exit_error("Invalid Plane normal", rt);
	if (!parse_color(tokens[3], &obj->data.pl.color))
		exit_error("Invalid Plane color", rt);
	add_object_to_scene(rt, obj);
}

void parse_cylinder(char **tokens, t_minirt *rt) {
	t_object *obj;

	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5] ||
		tokens[6])
		exit_error("Invalid Cylinder format", rt);
	obj = malloc(sizeof(t_object));
	if (!obj)
		exit_error("Malloc failed", rt);
	obj->type = CYLINDER;
	obj->next = NULL;
	if (!parse_vec3(tokens[1], &obj->data.cy.center))
		exit_error("Invalid Cylinder center", rt);
	if (!parse_vec3(tokens[2], &obj->data.cy.axis))
		exit_error("Invalid Cylinder axis", rt);
	obj->data.cy.diameter = ft_atof(tokens[3]);
	obj->data.cy.height = ft_atof(tokens[4]);
	if (!parse_color(tokens[5], &obj->data.cy.color))
		exit_error("Invalid Cylinder color", rt);
	add_object_to_scene(rt, obj);
}
