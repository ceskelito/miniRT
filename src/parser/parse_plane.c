/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:30:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/27 17:30:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int validate_plane_normal(t_vec3 *normal) {
	double len;

	len = sqrt(normal->x * normal->x + normal->y * normal->y +
			   normal->z * normal->z);
	if (len < 0.99 || len > 1.01)
		return (print_error(ERROR_INVALID_VECTOR), 0);
	return (1);
}

int parse_plane(char *line, t_scene *scene) {
	char **parts;
	t_plane *plane;
	t_object *obj;

	parts = ft_split(line, ' ');
	if (!parts || !parts[1] || !parts[2] || !parts[3])
		return (free_split(parts), 0);
	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (free_split(parts), 0);
	if (!parse_vec3(parts[1], &plane->point))
		return (free(plane), free_split(parts), 0);
	if (!parse_vec3(parts[2], &plane->normal))
		return (free(plane), free_split(parts), 0);
	if (!validate_plane_normal(&plane->normal))
		return (free(plane), free_split(parts), 0);
	if (!parse_color(parts[3], &plane->color))
		return (free(plane), free_split(parts), 0);
	free_split(parts);
	obj = create_object(OBJ_PLANE, plane);
	if (!obj)
		return (free(plane), 0);
	add_object(scene, obj);
	return (1);
}
