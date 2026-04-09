/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:30:13 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/09 18:25:03 by rceschel         ###   ########.fr       */
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
t_object	*get_selected_object(t_minirt *rt, int x, int y);
int			resize_object(t_object *selected, int resize_value);

int handle_mouse_events(int button, int x, int y, t_minirt *rt)
{
	// t_object	*selected;
	// int			resize_value;

	// if (button == MOUSE_LEFT)
	// 	resize_value = RESIZE_ABS_VALUE;
	// else if (button == MOUSE_RIGHT)
	// 	resize_value = RESIZE_ABS_VALUE * -1;
	// else
	// 	return (0);
	if (button == MOUSE_LEFT)
	{
		rt->scene.selected_object = get_selected_object(rt, x, y);
		render(rt);
	}
	// if (selected)
	// {
	// 	if (resize_object(selected, resize_value))
	// 		render(rt);
	// }
	return (0);
}

/*
 * Teoricamente la cosa migliore sarebbe solo ottenere l'oggetto selezionato,
 * poi mostrare una legenda,
 * e infine gestire i keypress per operare sull'oggetto (resize, move, ...).
 *
 * Questa è una soluzione rudimentale e temporanea che confonde le responsabilità
 * delle funzioni.
 *
 * Ricorda: handle_mouse_events deve solo fare routing verso altre funzioni,
 * adesso gestisce già troppa logica che non le compete.
 * */

/***** END OF MOUSE OBJECT SELECTION *****/

int rt_close_program(t_minirt *rt);
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
