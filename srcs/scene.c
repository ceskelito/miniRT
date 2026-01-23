/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:00:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/23 00:00:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>

/* Free every node of a libft list and its content. */
static void	free_list(t_list *list)
{
	t_list	*next;

	while (list != NULL)
	{
		next = list->next;
		free(list->content);
		free(list);
		list = next;
	}
}

/* Initialize all scene fields to a safe default state. */
void	scene_init(t_scene *scene)
{
	if (scene == NULL)
		return ;
	scene->ambient.intensity = 0.0;
	scene->ambient.color.r = 0;
	scene->ambient.color.g = 0;
	scene->ambient.color.b = 0;
	scene->ambient.present = false;
	scene->cameras = NULL;
	scene->lights = NULL;
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
}

/* Free all resources stored in a scene container. */
void	scene_clear(t_scene *scene)
{
	if (scene == NULL)
		return ;
	free_list(scene->cameras);
	free_list(scene->lights);
	free_list(scene->spheres);
	free_list(scene->planes);
	free_list(scene->cylinders);
	scene->cameras = NULL;
	scene->lights = NULL;
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
	scene->ambient.present = false;
}
