/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:00:00 by antigravit        #+#    #+#             */
/*   Updated: 2026/03/31 12:49:05 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include "parser.h"

static char	*add_object_to_scene(t_object **objects, t_object *new_obj)
{
	t_object	*curr;

	if (!new_obj)
		return (strerror(errno));
		// return ("Memory allocation failed for object");
	if (!*objects)
	{
		*objects = new_obj;
	}
	else
	{
		curr = *objects;
		while (curr->next)
			curr = curr->next;
		curr->next = new_obj;
	}
	return (NULL);
}
char	*parse_sphere(char **tokens, t_object **objects)
{
	t_object	*obj;
	char		*err;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return ("Invalid Sphere format");
	obj = malloc(sizeof(t_object));
	if (!obj)
		return (strerror(errno));//("Malloc failed");
	obj->type = SPHERE;
	obj->next = NULL;
	if (!parse_vec3(tokens[1], &obj->data.sp.center))
		return (free(obj), "Invalid Sphere center");
	obj->data.sp.diameter = ft_atof(tokens[2]);
	if (!parse_color(tokens[3], &obj->data.sp.color))
		return (free(obj), "Invalid Sphere color");
	err = add_object_to_scene(objects, obj);
	return (err);
}

char	*parse_plane(char **tokens, t_object **objects)
{
	t_object	*obj;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return ("Invalid Plane format");
	obj = malloc(sizeof(t_object));
	if (!obj)
		return (strerror(errno));//("Malloc failed");
	obj->type = PLANE;
	obj->next = NULL;
	if (!parse_vec3(tokens[1], &obj->data.pl.point))
		return (free(obj), "Invalid Plane point");
	if (!parse_vec3(tokens[2], &obj->data.pl.normal))
		return (free(obj), "Invalid Plane normal");
	if (!parse_color(tokens[3], &obj->data.pl.color))
		return (free(obj), "Invalid Plane color");
	return (add_object_to_scene(objects, obj));
}

char	*parse_cylinder(char **tokens, t_object **objects)
{
	t_object	*obj;

	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5]
		|| tokens[6])
		return ("Invalid Cylinder format");
	obj = malloc(sizeof(t_object));
	if (!obj)
		return (strerror(errno));//("Malloc failed");
	obj->type = CYLINDER;
	obj->next = NULL;
	if (!parse_vec3(tokens[1], &obj->data.cy.center))
		return (free(obj), "Invalid Cylinder center");
	if (!parse_vec3(tokens[2], &obj->data.cy.axis))
		return (free(obj), "Invalid Cylinder axis");
	obj->data.cy.diameter = ft_atof(tokens[3]);
	obj->data.cy.height = ft_atof(tokens[4]);
	if (!parse_color(tokens[5], &obj->data.cy.color))
		return (free(obj), "Invalid Cylinder color");
	return (add_object_to_scene(objects, obj));
}
