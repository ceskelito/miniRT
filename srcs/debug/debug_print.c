/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:00:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/23 00:00:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

/* Print ambient light data. */
extern void	debug_print_ambient(const t_ambient *ambient);

/* Print camera data for one list entry. */
extern void	debug_print_camera(void *content);

/* Print light data for one list entry. */
extern void	debug_print_light(void *content);

/* Print sphere data for one list entry. */
extern void	debug_print_sphere(void *content);

/* Print plane data for one list entry. */
extern void	debug_print_plane(void *content);

/* Print cylinder data for one list entry. */
extern void	debug_print_cylinder(void *content);

/* Print a list header and each entry with an index. */
static void	print_list(const char *title, t_list *list,
				void (*printer)(void *))
{
	int	index;

	printf("%s:\n", title);
	index = 1;
	while (list != NULL)
	{
		printf("  #%d\n", index);
		printer(list->content);
		list = list->next;
		index = index + 1;
	}
	if (index == 1)
		printf("  (none)\n");
}

/* Print parsed scene data to stdout for debugging. */
void	debug_print_scene(const t_scene *scene)
{
	if (scene == NULL)
		return ;
	printf("Scene debug output\n");
	debug_print_ambient(&scene->ambient);
	print_list("Cameras", scene->cameras, debug_print_camera);
	print_list("Lights", scene->lights, debug_print_light);
	print_list("Spheres", scene->spheres, debug_print_sphere);
	print_list("Planes", scene->planes, debug_print_plane);
	print_list("Cylinders", scene->cylinders, debug_print_cylinder);
}
