/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:30:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/27 17:30:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int parse_light(char *line, t_scene *scene) {
	char **parts;
	double brightness;
	int success;

	if (scene->light.is_set)
		return (print_error(ERROR_DUPLICATE_ELEMENT), 0);
	parts = ft_split(line, ' ');
	if (!parts || !parts[1] || !parts[2] || !parts[3])
		return (free_split(parts), 0);
	if (!parse_vec3(parts[1], &scene->light.position))
		return (free_split(parts), 0);
	brightness = ft_atof(parts[2]);
	if (brightness < 0.0 || brightness > 1.0)
		return (free_split(parts), 0);
	scene->light.brightness = brightness;
	success = parse_color(parts[3], &scene->light.color);
	free_split(parts);
	if (!success)
		return (0);
	scene->light.is_set = 1;
	return (1);
}
