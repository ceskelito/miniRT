/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_entities_a.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:00:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/23 00:00:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

/* Print a labeled vector with fixed precision. */
extern void	debug_print_vec3(const char *label, t_vec3 v);

/* Print a labeled RGB color. */
extern void	debug_print_color(const char *label, t_color c);

/* Print ambient light data. */
void	debug_print_ambient(const t_ambient *ambient)
{
	if (ambient == NULL || !ambient->present)
	{
		printf("Ambient: (none)\n");
		return ;
	}
	printf("Ambient:\n");
	printf("  intensity: %.3f\n", ambient->intensity);
	debug_print_color("  color", ambient->color);
}

/* Print camera data for one list entry. */
void	debug_print_camera(void *content)
{
	t_camera	*camera;

	camera = (t_camera *)content;
	if (camera == NULL)
		return ;
	debug_print_vec3("    position", camera->pos);
	debug_print_vec3("    direction", camera->dir);
	printf("    fov: %.3f\n", camera->fov);
}

/* Print light data for one list entry. */
void	debug_print_light(void *content)
{
	t_light	*light;

	light = (t_light *)content;
	if (light == NULL)
		return ;
	debug_print_vec3("    position", light->pos);
	printf("    intensity: %.3f\n", light->intensity);
	debug_print_color("    color", light->color);
}

/* Print sphere data for one list entry. */
void	debug_print_sphere(void *content)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)content;
	if (sphere == NULL)
		return ;
	debug_print_vec3("    center", sphere->center);
	printf("    diameter: %.3f\n", sphere->diameter);
	debug_print_color("    color", sphere->color);
}

/* Print plane data for one list entry. */
void	debug_print_plane(void *content)
{
	t_plane	*plane;

	plane = (t_plane *)content;
	if (plane == NULL)
		return ;
	debug_print_vec3("    point", plane->point);
	debug_print_vec3("    normal", plane->normal);
	debug_print_color("    color", plane->color);
}
