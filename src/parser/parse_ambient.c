/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:30:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/27 17:30:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int parse_ambient(char *line, t_scene *scene) {
	char **parts;
	double ratio;
	int success;

	if (scene->ambient.is_set)
		return (print_error(ERROR_DUPLICATE_ELEMENT), 0);
	parts = ft_split(line, ' ');
	if (!parts || !parts[1] || !parts[2])
		return (free_split(parts), 0);
	ratio = ft_atof(parts[1]);
	if (ratio < 0.0 || ratio > 1.0)
		return (free_split(parts), 0);
	scene->ambient.ratio = ratio;
	success = parse_color(parts[2], &scene->ambient.color);
	free_split(parts);
	if (!success)
		return (0);
	scene->ambient.is_set = 1;
	return (1);
}
