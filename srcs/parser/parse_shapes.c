/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:00:00 by antigravit        #+#    #+#             */
/*   Updated: 2026/04/07 10:40:04 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include "parser.h"

char	*parse_sphere(char **tokens, t_object **objects)
{
	t_object	*obj;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return ("Invalid Sphere format");
	obj = malloc(sizeof(t_object));
	if (!obj)
		return (strerror(errno));
	obj->type = SPHERE;
	obj->next = NULL;
	if (!parse_vec3(tokens[1], &obj->data.sp.center))
		return (free(obj), "Invalid Sphere center");
	obj->data.sp.diameter = ft_atof(tokens[2]);
	if (!parse_color(tokens[3], &obj->data.sp.color))
		return (free(obj), "Invalid Sphere color");
	return (add_object_to_scene(objects, obj));
}

char	*parse_plane(char **tokens, t_object **objects)
{
	t_object	*obj;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return ("Invalid Plane format");
	obj = malloc(sizeof(t_object));
	if (!obj)
		return (strerror(errno));
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
		return (strerror(errno));
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

char	*parse_cone(char **tokens, t_object **objects)
{
	t_object	*obj;

	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5]
		|| tokens[6])
		return ("Invalid Cone format");
	obj = malloc(sizeof(t_object));
	if (!obj)
		return (strerror(errno));
	obj->type = CONE;
	obj->next = NULL;
	if (!parse_vec3(tokens[1], &obj->data.co.center))
		return (free(obj), "Invalid Cone center");
	if (!parse_vec3(tokens[2], &obj->data.co.axis))
		return (free(obj), "Invalid Cone axis");
	obj->data.co.diameter = ft_atof(tokens[3]);
	obj->data.co.height = ft_atof(tokens[4]);
	if (!parse_color(tokens[5], &obj->data.co.color))
		return (free(obj), "Invalid Cone color");
	return (add_object_to_scene(objects, obj));
}

char	*parse_torus(char **tokens, t_object **objects)
{
	t_object	*obj;

	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5]
		|| tokens[6])
		return ("Invalid Torus format");
	obj = malloc(sizeof(t_object));
	if (!obj)
		return (strerror(errno));
	obj->type = TORUS;
	obj->next = NULL;
	if (!parse_vec3(tokens[1], &obj->data.to.coords))
		return (free(obj), "Invalid Torus center");
	if (!parse_vec3(tokens[2], &obj->data.to.orient))
		return (free(obj), "Invalid Torus orient");
	obj->data.to.big_r = (float)ft_atof(tokens[3]);
	obj->data.to.big_r2 = obj->data.to.big_r * obj->data.to.big_r;
	obj->data.to.sml_r = (float)ft_atof(tokens[4]);
	obj->data.to.sml_r2 = obj->data.to.sml_r * obj->data.to.sml_r;
	if (!parse_color(tokens[5], &obj->data.to.color))
		return (free(obj), "Invalid Torus color");
	return (add_object_to_scene(objects, obj));
}
