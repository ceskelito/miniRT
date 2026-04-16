/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:08:20 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/09 18:17:04 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"
#include "mlx.h"

int	handle_keypress(int keycode, t_minirt *rt);
int	handle_mouse_events(int button, int x, int y, t_minirt *rt);

static int	mlx_init_instance(void **mlx_ptr, void **win_ptr,
	int size[2], char *name)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	if (!mlx)
		return (1);
	win = mlx_new_window(mlx, size[0], size[1], name);
	if (!win)
	{
		free(mlx);
		return (1);
	}
	*mlx_ptr = mlx;
	*win_ptr = win;
	return (0);
}

int	mlx_close_window(t_mlx *mlx)
{
	if (mlx->win)
		mlx_destroy_window(mlx->ptr, mlx->win);
	if (mlx->ptr)
	{
		mlx_destroy_display(mlx->ptr);
		free(mlx->ptr);
	}
	return (0);
}

int	rt_close_program(t_minirt *rt)
{
	mlx_close_window(&rt->mlx);
	free_scene(&rt->scene);
	exit(EXIT_SUCCESS);
}

int	mlx_loop_init(t_minirt *rt)
{
	int	size[2];

	size[0] = WIN_WIDTH;
	size[1] = WIN_HEIGHT;
	if (mlx_init_instance(&(rt->mlx.ptr), &(rt->mlx.win), size, WIN_NAME))
		exit(1);
	rt->width = WIN_WIDTH;
	rt->height = WIN_HEIGHT;
	render(rt);
	mlx_hook(rt->mlx.win, 17, 0, rt_close_program, rt);
	mlx_hook(rt->mlx.win, 2, 1L << 0, handle_keypress, rt);
	mlx_mouse_hook(rt->mlx.win, handle_mouse_events, rt);
	mlx_loop(rt->mlx.ptr);
	return (0);
}
