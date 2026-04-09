/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:08:20 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/09 17:27:33 by rceschel         ###   ########.fr       */
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

/***** START OF MOUSE OBJECT SELECTION *****/

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

static t_object *get_selected_object(t_minirt *rt, int x, int y)
{
    t_hit		closest_hit;
    t_hit		current_hit;
    t_object	*curr;
	t_object	*closest;
	t_ray		ray;

    closest_hit.t = INFINITY; // Start from infinity
    curr = rt->scene.objects;

    while (curr)
    {
		ray = camera_ray(rt->scene.camera, x, y, rt->width, rt->height);
        if (intersect(ray, curr, &current_hit)) // Intersection dispatcher by currect type
        {
            if (current_hit.t < closest_hit.t)
			{
                closest_hit = current_hit;
				closest = curr;
			}
        }
        curr = curr->next;
    }

    if (closest_hit.t == INFINITY)
		return (NULL);
	return (closest);
}

#define RESIZE_ABS_VALUE 5

enum { MOUSE_LEFT = 1, MOUSE_RIGHT = 3, MOUSE_CENTER = 2, SCROLL_UP = 4, SCROLL_DOWN = 5 };

int handle_mouse_events(int button, int x, int y, t_minirt *rt)
{
	t_object	*selected;
	int			resize_value;

	if (button == MOUSE_LEFT)
		resize_value = RESIZE_ABS_VALUE;
	else if (button == MOUSE_RIGHT)
		resize_value = RESIZE_ABS_VALUE * -1;
	else
		return (0);
	selected = get_selected_object(rt, x, y);
	if (selected)
	{
		if (selected->type == SPHERE)
			selected->data.sp.diameter += resize_value;
		else if (selected->type == CYLINDER)
		{
			selected->data.cy.diameter += resize_value;
			selected->data.cy.height += resize_value;
		}
		else
			return 0;
		render(rt);
	}
	return (0);
}

/***** END OF MOUSE OBJECT SELECTION *****/

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

