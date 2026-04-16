/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:00:00 by antigravit        #+#    #+#             */
/*   Updated: 2026/04/09 18:27:24 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "legend.h"

int	main(int argc, char **argv)
{
	t_minirt	rt;

	if (argc != 2)
	{
		ft_dprintf(2, "Usage: ./miniRT <filename.rt>\n");
		return (1);
	}
	rt.scene.objects = NULL;
	rt.scene.selected_object = NULL;
	rt.scene.selected_light = NULL;
	rt.scene.expanded_legend = NO_LEGEND;
	rt.mlx.ptr = NULL;
	rt.mlx.win = NULL;
	parse_scene(argv[1], &rt);
	/* Open window, render the scene, then enter the MLX event loop.
	** rt_close_program (ESC / X button) handles cleanup and exit. */
	mlx_loop_init(&rt);
	return (0);
}
