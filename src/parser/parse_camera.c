/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:30:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/27 17:30:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int validate_camera(t_camera *camera) {
	double len;
	int fov;

	len = sqrt(camera->orientation.x * camera->orientation.x +
			   camera->orientation.y * camera->orientation.y +
			   camera->orientation.z * camera->orientation.z);
	if (len < 0.99 || len > 1.01)
		return (print_error(ERROR_INVALID_VECTOR), 0);
	fov = camera->fov;
	if (fov < 0 || fov > 180)
		return (print_error(ERROR_INVALID_RANGE), 0);
	return (1);
}

int parse_camera(char *line, t_scene *scene) {
	char **parts;
	int fov;
	int success;

	if (scene->camera.is_set)
		return (print_error(ERROR_DUPLICATE_ELEMENT), 0);
	parts = ft_split(line, ' ');
	if (!parts || !parts[1] || !parts[2] || !parts[3])
		return (free_split(parts), 0);
	if (!parse_vec3(parts[1], &scene->camera.position))
		return (free_split(parts), 0);
	if (!parse_vec3(parts[2], &scene->camera.orientation))
		return (free_split(parts), 0);
	fov = ft_atoi(parts[3]);
	scene->camera.fov = fov;
	free_split(parts);
	success = validate_camera(&scene->camera);
	if (!success)
		return (0);
	scene->camera.is_set = 1;
	return (1);
}
