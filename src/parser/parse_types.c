/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:30:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/27 17:30:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int parse_vec3(const char *str, t_vec3 *vec) {
	char **parts;
	int success;

	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2]) {
		if (parts)
			free_split(parts);
		return (0);
	}
	vec->x = ft_atof(parts[0]);
	vec->y = ft_atof(parts[1]);
	vec->z = ft_atof(parts[2]);
	success = (parts[3] == NULL);
	free_split(parts);
	return (success);
}

int parse_color(const char *str, t_color *color) {
	char **parts;
	int r;
	int g;
	int b;

	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2]) {
		if (parts)
			free_split(parts);
		return (0);
	}
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	free_split(parts);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	color->r = r;
	color->g = g;
	color->b = b;
	return (1);
}
