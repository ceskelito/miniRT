/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:00:00 by antigravit        #+#    #+#             */
/*   Updated: 2026/04/15 16:18:37 by rceschel         ###   ########.fr       */
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
	rt.scene.focused_op_legend = NO_LEGEND;
	rt.scene.focused_right_legend = NO_LEGEND;
	rt.mlx.ptr = NULL;
	rt.mlx.win = NULL;
	parse_scene(argv[1], &rt);
	mlx_loop_init(&rt);
	return (0);
}
