/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:30:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/27 17:30:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void init_scene(t_scene *scene) {
	scene->ambient.is_set = 0;
	scene->camera.is_set = 0;
	scene->light.is_set = 0;
	scene->objects = NULL;
}

t_object *create_object(int type, void *data) {
	t_object *obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->type = type;
	obj->data = data;
	obj->next = NULL;
	return (obj);
}

void add_object(t_scene *scene, t_object *obj) {
	t_object *current;

	if (!scene->objects) {
		scene->objects = obj;
		return;
	}
	current = scene->objects;
	while (current->next)
		current = current->next;
	current->next = obj;
}
