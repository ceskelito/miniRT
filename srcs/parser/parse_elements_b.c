/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:00:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/23 00:00:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>

/* Append a sphere object to the scene list. */
static t_parse_error	add_sphere(t_scene *scene, t_sphere *sphere)
{
	t_list	*node;

	node = ft_lstnew(sphere);
	if (node == NULL)
	{
		free(sphere);
		return (PARSE_ERR_MEM);
	}
	ft_lstadd_back(&scene->spheres, node);
	return (PARSE_OK);
}

/* Build sphere data and append it to the scene list. */
static t_parse_error	build_sphere(char **parts, t_scene *scene)
{
	t_sphere	*sphere;
	double		diameter;

	sphere = malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (PARSE_ERR_MEM);
	if (!parse_vec3(parts[1], &sphere->center)
		|| !parse_double(parts[2], &diameter)
		|| !parse_color(parts[3], &sphere->color))
	{
		free(sphere);
		return (PARSE_ERR_RANGE);
	}
	if (diameter <= 0.0)
	{
		free(sphere);
		return (PARSE_ERR_RANGE);
	}
	sphere->diameter = diameter;
	return (add_sphere(scene, sphere));
}

/* Parse sphere line into the scene. */
t_parse_error	parse_sphere_line(char **parts, t_scene *scene)
{
	if (!parts[1] || !parts[2] || !parts[3] || parts[4])
		return (PARSE_ERR_SYNTAX);
	return (build_sphere(parts, scene));
}

