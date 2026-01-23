/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_c.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:00:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/23 00:00:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>

/* Validate normalized cylinder axis. */
static int	axis_is_valid(t_vec3 axis)
{
	if (axis.x < -1.0 || axis.x > 1.0)
		return (0);
	if (axis.y < -1.0 || axis.y > 1.0)
		return (0);
	if (axis.z < -1.0 || axis.z > 1.0)
		return (0);
	if (axis.x == 0.0 && axis.y == 0.0 && axis.z == 0.0)
		return (0);
	return (1);
}

/* Append a cylinder object to the scene list. */
static t_parse_error	add_cylinder(t_scene *scene, t_cylinder *cyl)
{
	t_list	*node;

	node = ft_lstnew(cyl);
	if (node == NULL)
	{
		free(cyl);
		return (PARSE_ERR_MEM);
	}
	ft_lstadd_back(&scene->cylinders, node);
	return (PARSE_OK);
}

/* Parse cylinder fields and basic parameters. */
static int	fill_cylinder(char **parts, t_cylinder *cyl,
		double *diameter, double *height)
{
	if (!parse_vec3(parts[1], &cyl->pos)
		|| !parse_vec3(parts[2], &cyl->axis)
		|| !parse_double(parts[3], diameter)
		|| !parse_double(parts[4], height)
		|| !parse_color(parts[5], &cyl->color))
		return (0);
	return (1);
}

/* Build cylinder data and append it to the scene list. */
static t_parse_error	build_cylinder(char **parts, t_scene *scene)
{
	t_cylinder	*cyl;
	double		diameter;
	double		height;

	cyl = malloc(sizeof(t_cylinder));
	if (cyl == NULL)
		return (PARSE_ERR_MEM);
	if (!fill_cylinder(parts, cyl, &diameter, &height))
	{
		free(cyl);
		return (PARSE_ERR_RANGE);
	}
	if (!axis_is_valid(cyl->axis) || diameter <= 0.0 || height <= 0.0)
	{
		free(cyl);
		return (PARSE_ERR_RANGE);
	}
	cyl->diameter = diameter;
	cyl->height = height;
	return (add_cylinder(scene, cyl));
}

/* Parse cylinder line into the scene. */
t_parse_error	parse_cylinder_line(char **parts, t_scene *scene)
{
	if (!parts[1] || !parts[2] || !parts[3] || !parts[4] || !parts[5]
		|| parts[6])
		return (PARSE_ERR_SYNTAX);
	return (build_cylinder(parts, scene));
}
