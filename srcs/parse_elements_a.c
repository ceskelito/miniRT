/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_a.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:00:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/23 00:00:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>

/* Validate normalized direction vectors. */
static int	dir_is_valid(t_vec3 dir)
{
	if (dir.x < -1.0 || dir.x > 1.0)
		return (0);
	if (dir.y < -1.0 || dir.y > 1.0)
		return (0);
	if (dir.z < -1.0 || dir.z > 1.0)
		return (0);
	if (dir.x == 0.0 && dir.y == 0.0 && dir.z == 0.0)
		return (0);
	return (1);
}

/* Parse ambient light line into the scene. */
t_parse_error	parse_ambient_line(char **parts, t_scene *scene)
{
	double	intensity;

	if (scene->ambient.present)
		return (PARSE_ERR_DUPLICATE);
	if (!parts[1] || !parts[2] || parts[3])
		return (PARSE_ERR_SYNTAX);
	if (!parse_double(parts[1], &intensity)
		|| intensity < 0.0 || intensity > 1.0)
		return (PARSE_ERR_RANGE);
	if (!parse_color(parts[2], &scene->ambient.color))
		return (PARSE_ERR_RANGE);
	scene->ambient.intensity = intensity;
	scene->ambient.present = true;
	return (PARSE_OK);
}

/* Append a camera object to the scene list. */
static t_parse_error	add_camera(t_scene *scene, t_camera *camera)
{
	t_list	*node;

	node = ft_lstnew(camera);
	if (node == NULL)
	{
		free(camera);
		return (PARSE_ERR_MEM);
	}
	ft_lstadd_back(&scene->cameras, node);
	return (PARSE_OK);
}

/* Build camera data and append it to the scene list. */
static t_parse_error	build_camera(char **parts, t_scene *scene)
{
	t_camera	*camera;
	double		fov;

	camera = malloc(sizeof(t_camera));
	if (camera == NULL)
		return (PARSE_ERR_MEM);
	if (!parse_vec3(parts[1], &camera->pos)
		|| !parse_vec3(parts[2], &camera->dir)
		|| !parse_double(parts[3], &fov))
	{
		free(camera);
		return (PARSE_ERR_RANGE);
	}
	if (!dir_is_valid(camera->dir) || fov <= 0.0 || fov > 180.0)
	{
		free(camera);
		return (PARSE_ERR_RANGE);
	}
	camera->fov = fov;
	return (add_camera(scene, camera));
}

/* Parse camera line into the scene. */
t_parse_error	parse_camera_line(char **parts, t_scene *scene)
{
	if (scene->cameras != NULL)
		return (PARSE_ERR_DUPLICATE);
	if (!parts[1] || !parts[2] || !parts[3] || parts[4])
		return (PARSE_ERR_SYNTAX);
	return (build_camera(parts, scene));
}
