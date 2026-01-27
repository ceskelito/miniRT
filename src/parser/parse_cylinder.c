/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:30:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/27 17:30:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int validate_cyl_axis(t_vec3 *axis) {
	double len;

	len = sqrt(axis->x * axis->x + axis->y * axis->y + axis->z * axis->z);
	if (len < 0.99 || len > 1.01)
		return (print_error(ERROR_INVALID_VECTOR), 0);
	return (1);
}

static int validate_cyl_dims(double diameter, double height) {
	if (diameter <= 0 || height <= 0)
		return (print_error(ERROR_INVALID_VALUE), 0);
	return (1);
}

int parse_cylinder(char *line, t_scene *scene) {
	char **parts;
	t_cylinder *cyl;
	t_object *obj;

	parts = ft_split(line, ' ');
	if (!parts || !parts[1] || !parts[2] || !parts[3] || !parts[4] || !parts[5])
		return (free_split(parts), 0);
	cyl = malloc(sizeof(t_cylinder));
	if (!cyl)
		return (free_split(parts), 0);
	if (!parse_vec3(parts[1], &cyl->center) ||
		!parse_vec3(parts[2], &cyl->axis))
		return (free(cyl), free_split(parts), 0);
	if (!validate_cyl_axis(&cyl->axis))
		return (free(cyl), free_split(parts), 0);
	cyl->diameter = ft_atof(parts[3]);
	cyl->height = ft_atof(parts[4]);
	if (!validate_cyl_dims(cyl->diameter, cyl->height) ||
		!parse_color(parts[5], &cyl->color))
		return (free(cyl), free_split(parts), 0);
	free_split(parts);
	obj = create_object(OBJ_CYLINDER, cyl);
	if (!obj)
		return (free(cyl), 0);
	add_object(scene, obj);
	return (1);
}
