/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:00:00 by antigravit        #+#    #+#             */
/*   Updated: 2026/02/06 18:01:18 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <X11/keysym.h>
#include "parser.h"

int	mlx_data_init(void **mlx_ptr, void **win_ptr, int w_l, int w_h, char *w_name)
{
	*mlx_ptr = mlx_init();
	if (!*mlx_ptr)
		return (1);
	*win_ptr = mlx_new_window(*mlx_ptr, w_l, w_h, w_name);
	if (!*win_ptr)
	{
		free(*mlx_ptr);
		return (1);
	}
	return (0);
}

int	close_window(t_minirt *rt)
{
	mlx_destroy_window(rt->mlx, rt->win);
	mlx_destroy_display(rt->mlx);
	free_scene(rt);
	return (0);
}

int	handle_keypress(int keycode, t_minirt *rt)
{
	if (keycode == XK_Escape)
		close_window(rt);
	// else if (keycode == XK_Left || keycode == XK_a)
	// 	win = move_player(map, -1, 0);
	// else if (keycode == XK_Right || keycode == XK_d)
	// 	win = move_player(map, 1, 0);
	// else if (keycode == XK_Up || keycode == XK_w)
	// 	win = move_player(map, 0, -1);
	// else if (keycode == XK_Down || keycode == XK_s)
	// 	win = move_player(map, 0, 1);
	// if (win)
	// {
	//		ft_printf("Moves count: %i\n", map->player.moves + 1);
	//		ft_printf("Error\nToo skilled player has won the game\n");
	// 	close_window(map);
	// }
	return (0);
}

int	main(int argc, char **argv)
{
	t_minirt	rt;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./miniRT <filename.rt>\n", 2);
		return (1);
	}
	rt.scene.objects = NULL;
	rt.mlx = NULL;
	rt.win = NULL;
	printf("Parsing scene: %s\n", argv[1]);
	parse_scene(argv[1], &rt);
	printf("Parsing complete. Verifying data:\n");
	print_scene(&rt);
	if (mlx_data_init(&(rt.mlx), &(rt.win), WIN_WIDTH, WIN_HEIGHT, WIN_NAME) != 0)
		return (1);
	if (!rt.mlx || !rt.win)
		return (ft_printf("NONEE"), 1);
	mlx_loop_hook(rt.win, NULL, NULL);
	mlx_hook(rt.win, 17, 0, &close_window, &rt);
	mlx_hook(rt.win, 2, 1L << 0, &handle_keypress, &rt);
	mlx_loop(rt.mlx);
	close_window(&rt);
	return (0);
}
