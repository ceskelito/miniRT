/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:30:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/27 17:30:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int parse_sphere(char *line, t_scene *scene) {
	char **parts;
	t_sphere *sphere;
	t_object *obj;

	parts = ft_split(line, ' ');
	if (!parts || !parts[1] || !parts[2] || !parts[3])
		return (free_split(parts), 0);
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (free_split(parts), 0);
	if (!parse_vec3(parts[1], &sphere->center))
		return (free(sphere), free_split(parts), 0);
	sphere->diameter = ft_atof(parts[2]);
	if (sphere->diameter <= 0)
		return (free(sphere), free_split(parts), 0);
	if (!parse_color(parts[3], &sphere->color))
		return (free(sphere), free_split(parts), 0);
	free_split(parts);
	obj = create_object(OBJ_SPHERE, sphere);
	if (!obj)
		return (free(sphere), 0);
	add_object(scene, obj);
	return (1);
}
