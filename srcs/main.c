/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:00:00 by antigravit        #+#    #+#             */
/*   Updated: 2026/03/30 17:45:03 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int mlx_loop_init(t_minirt *rt);
int	mlx_close_window(void *mlx_ptr, void *mlx_win);

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
	// mlx_loop_init(&rt);

	// You're code here

	// mlx_close_window(rt->mlx, rt->win);
	free_scene(&rt.scene);
	return (0);
}
