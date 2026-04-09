/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:08:20 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/09 16:31:33 by rceschel         ###   ########.fr       */
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

int	mlx_close_window(t_mlx *mlx)
{
	if (mlx->win)
		mlx_destroy_window(mlx->ptr, mlx->win);
	if (mlx->ptr) {
		mlx_destroy_display(mlx->ptr);
		free(mlx->ptr);
	}
	return (0);
}

int rt_close_program(t_minirt *rt)
{
	mlx_close_window(&rt->mlx);
	free_scene(&rt->scene);
	exit(EXIT_SUCCESS);
}

static int	handle_keypress(int keycode, t_minirt *rt)
{
	if (keycode == XK_Escape)
		rt_close_program(rt);
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

/*
 * How to handle events:
 *
 * 1. On left click, check if the coordinates intersect an object
 *		(maybe we have an appropriate function yet..?)
 *		USE THE INTERSECT: shot a ray like for rendering
 *
 * 2. In case of, higlith the object
 * 2.1 Display a legend of possible commands
 *
 * 3. Apply trasformation on the selected object
 * */
t_ray	camera_ray(t_camera cam, int px, int py, int w, int h);

/*
 * An object is found if at least one of the color gradient is not balck (background)
 * */
static bool is_object_selected(t_minirt *rt, int x, int y)
{
	t_color test;

	test = trace_ray(&rt->scene, camera_ray(rt->scene.camera, x, y, rt->width, rt->height));
	return (test.r || test.g || test.b);
}

int handle_mouse_events(int button, int x, int y, t_minirt *rt)
{
	if ( button == 1 && is_object_selected(rt, x, y))
		printf("YEEEEEEEEE\n");
	return (0);
}

int mlx_loop_init(t_minirt *rt)
{
	bool	mlx_failure;

	mlx_failure = mlx_init_instance(&(rt->mlx.ptr), &(rt->mlx.win),
							WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	if (mlx_failure)
		exit(1);
	/* Store final dimensions so render() can use them */
	rt->width = WIN_WIDTH;
	rt->height = WIN_HEIGHT;
	/* Render the scene once into the window before entering the event loop */
	render(rt);
	/* Event 17 = window close (X button), event 2 = key press */
	mlx_hook(rt->mlx.win, 17, 0, rt_close_program, rt);
	mlx_hook(rt->mlx.win, 2, 1L << 0, handle_keypress, rt);
	mlx_mouse_hook(rt->mlx.win, handle_mouse_events, rt);
	mlx_loop(rt->mlx.ptr);
	return (0);
}

