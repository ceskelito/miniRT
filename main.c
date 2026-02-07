/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:00:00 by antigravit        #+#    #+#             */
/*   Updated: 2026/02/07 18:13:32 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int mlx_loop_init(t_minirt *rt);
int	mlx_close_window(t_minirt *rt); // exit the program

int	main(int argc, char **argv)
{
	t_minirt	rt;

	if (argc != 2)
	{
		ft_dprintf(2, "Usage: ./miniRT <filename.rt>\n");
		return (1);
	}
	rt.scene.objects = NULL;
	rt.mlx = NULL;
	rt.win = NULL;
	parse_scene(argv[1], &rt);
	print_scene(&rt);
	mlx_loop_init(&rt);
	mlx_close_window(&rt);
	return (0);
}
