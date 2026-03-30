/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:08:20 by rceschel          #+#    #+#             */
/*   Updated: 2026/03/30 15:10:18 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"
#include "mlx.h"
#include <X11/keysym.h>

static int	mlx_init_instance(void **mlx_ptr, void **win_ptr, int w_l, int w_h, char *w_name)
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
	mlx = NULL;
	win = NULL;
	return (0);
}

int	mlx_close_window(void *mlx_ptr, void *mlx_win)//t_minirt *rt)
{
	if (mlx_win)
		mlx_destroy_window(mlx_ptr, mlx_win);
	if (mlx_ptr) {
		mlx_destroy_display(mlx_ptr);
		free(mlx_ptr);
	}
	exit(EXIT_SUCCESS);
}

static int	handle_keypress(int keycode, t_minirt *rt)
{
	if (keycode == XK_Escape)
		mlx_close_window(rt->mlx, rt->win);
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

	mlx_failure = mlx_init_instance(&(rt->mlx), &(rt->win), 
							WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	if (mlx_failure)
		exit(1);
	mlx_loop_hook(rt->win, NULL, NULL);
	mlx_hook(rt->win, 17, 0, &mlx_close_window, rt);
	mlx_hook(rt->win, 2, 1L << 0, &handle_keypress, rt);
	mlx_loop(rt->mlx);

	return (0);
}

