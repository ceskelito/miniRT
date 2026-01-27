/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:30:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/27 17:30:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void free_object(t_object *obj) {
	if (!obj)
		return;
	if (obj->data)
		free(obj->data);
	free(obj);
}

void cleanup_scene(t_scene *scene) {
	t_object *current;
	t_object *next;

	if (!scene)
		return;
	current = scene->objects;
	while (current) {
		next = current->next;
		free_object(current);
		current = next;
	}
	scene->objects = NULL;
}
