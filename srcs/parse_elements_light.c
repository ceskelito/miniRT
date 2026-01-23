/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_light.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:00:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/23 00:00:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>

/* Append a light object to the scene list. */
static t_parse_error	add_light(t_scene *scene, t_light *light)
{
	t_list	*node;

	node = ft_lstnew(light);
	if (node == NULL)
	{
		free(light);
		return (PARSE_ERR_MEM);
	}
	ft_lstadd_back(&scene->lights, node);
	return (PARSE_OK);
}

/* Build light data and append it to the scene list. */
static t_parse_error	build_light(char **parts, t_scene *scene)
{
	t_light	*light;
	double	intensity;

	light = malloc(sizeof(t_light));
	if (light == NULL)
		return (PARSE_ERR_MEM);
	if (!parse_vec3(parts[1], &light->pos)
		|| !parse_double(parts[2], &intensity)
		|| !parse_color(parts[3], &light->color))
	{
		free(light);
		return (PARSE_ERR_RANGE);
	}
	if (intensity < 0.0 || intensity > 1.0)
	{
		free(light);
		return (PARSE_ERR_RANGE);
	}
	light->intensity = intensity;
	return (add_light(scene, light));
}

/* Parse light line into the scene. */
t_parse_error	parse_light_line(char **parts, t_scene *scene)
{
	if (!parts[1] || !parts[2] || !parts[3] || parts[4])
		return (PARSE_ERR_SYNTAX);
	return (build_light(parts, scene));
}
