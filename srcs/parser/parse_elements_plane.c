/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_plane.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:00:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/23 00:00:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>

/* Validate normalized plane normals. */
static int	normal_is_valid(t_vec3 normal)
{
	if (normal.x < -1.0 || normal.x > 1.0)
		return (0);
	if (normal.y < -1.0 || normal.y > 1.0)
		return (0);
	if (normal.z < -1.0 || normal.z > 1.0)
		return (0);
	if (normal.x == 0.0 && normal.y == 0.0 && normal.z == 0.0)
		return (0);
	return (1);
}

/* Append a plane object to the scene list. */
static t_parse_error	add_plane(t_scene *scene, t_plane *plane)
{
	t_list	*node;

	node = ft_lstnew(plane);
	if (node == NULL)
	{
		free(plane);
		return (PARSE_ERR_MEM);
	}
	ft_lstadd_back(&scene->planes, node);
	return (PARSE_OK);
}

/* Build plane data and append it to the scene list. */
static t_parse_error	build_plane(char **parts, t_scene *scene)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (plane == NULL)
		return (PARSE_ERR_MEM);
	if (!parse_vec3(parts[1], &plane->point)
		|| !parse_vec3(parts[2], &plane->normal)
		|| !parse_color(parts[3], &plane->color))
	{
		free(plane);
		return (PARSE_ERR_RANGE);
	}
	if (!normal_is_valid(plane->normal))
	{
		free(plane);
		return (PARSE_ERR_RANGE);
	}
	return (add_plane(scene, plane));
}

/* Parse plane line into the scene. */
t_parse_error	parse_plane_line(char **parts, t_scene *scene)
{
	if (!parts[1] || !parts[2] || !parts[3] || parts[4])
		return (PARSE_ERR_SYNTAX);
	return (build_plane(parts, scene));
}
