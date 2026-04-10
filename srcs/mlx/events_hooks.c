/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:30:13 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/10 15:12:23 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <X11/keysym.h>

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

/* Functions from:
 * srcs/objects/objects_utils.c 
 *
 * I will create an header
 * */

int print_legend(t_minirt *rt);
int handle_mouse_events(int button, int x, int y, t_minirt *rt)
{

	if (button == MOUSE_LEFT)
	{
		rt->scene.selected_object = get_selected_object(rt, x, y);
		// render(rt);
		print_legend(rt);
	}
	return (0);
}

/***** END OF MOUSE OBJECT SELECTION *****/

int	handle_keypress(int keycode, t_minirt *rt)
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
