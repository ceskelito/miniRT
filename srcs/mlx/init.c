/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:08:20 by rceschel          #+#    #+#             */
/*   Updated: 2026/02/07 18:12:05 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"
#include "mlx.h"
#include <X11/keysym.h>

int	mlx_data_init(void **mlx_ptr, void **win_ptr, int w_l, int w_h, char *w_name)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	if (!mlx)
		return (1);
	win = mlx_new_window(mlx, w_l, w_h, w_name);
	if (!win)
	{
		free(mlx);
		return (1);
	}
	*mlx_ptr = mlx;
	*win_ptr = win;
	return (0);
}

int	close_window(t_minirt *rt)
{
	if (rt->win)
		mlx_destroy_window(rt->mlx, rt->win);
	if (rt->mlx)
		mlx_destroy_display(rt->mlx);
	free_scene(rt);
	exit(0);
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

int mlx_loop_init(t_minirt *rt) {
	
	bool	mlx_failure;

	mlx_failure = mlx_data_init(&(rt->mlx), &(rt->win), 
							WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	if (mlx_failure)
		return (1);
	mlx_loop_hook(rt->win, NULL, NULL);
	mlx_hook(rt->win, 17, 0, &close_window, rt);
	mlx_hook(rt->win, 2, 1L << 0, &handle_keypress, rt);
	mlx_loop(rt->mlx);

	return (0);
}

