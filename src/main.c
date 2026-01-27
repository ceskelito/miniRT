/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:30:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/27 17:30:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int main(int argc, char **argv) {
	t_scene scene;

	if (argc != 2) {
		ft_printf("Usage: %s <scene.rt>\n", argv[0]);
		return (1);
	}
	if (!parse_scene_file(argv[1], &scene)) {
		ft_printf("Failed to parse scene file\n");
		return (1);
	}
	debug_print_scene(scene);
	cleanup_scene(&scene);
	return (0);
}
