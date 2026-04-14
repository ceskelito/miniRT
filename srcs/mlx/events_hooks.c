/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:30:13 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/14 17:51:31 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "legend.h"
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

int handle_mouse_events(int button, int x, int y, t_minirt *rt)
{

	if (button == MOUSE_LEFT)
	{
		rt->scene.selected_object = get_selected_object(rt, x, y);
		if (rt->scene.expanded_legend == NO_LEGEND)
			rt->scene.expanded_legend = RESIZE;
		if (rt->scene.selected_object)
			print_legend(rt);
		else
		{
			rt->scene.expanded_legend = NO_LEGEND;
			render(rt); // I need to render all the scene in order to remove the legend from the screen
						// Maybe we can work on an ad-hoc function to render only a section
		}
	}
	return (0);
}

/***** END OF MOUSE OBJECT SELECTION *****/

int	handle_keypress(int keycode, t_minirt *rt)
{
	if (keycode == XK_Escape)
		rt_close_program(rt);

	if (rt->scene.selected_object != NULL)
	{
		if (keycode == XK_1)
			rt->scene.expanded_legend = RESIZE;
		else if (keycode == XK_2)
			rt->scene.expanded_legend = TRANSFORM;
		else if (keycode == XK_3)
			rt->scene.expanded_legend = ROTATE;
		print_legend(rt);
	}
	if (rt->scene.expanded_legend == RESIZE && rt->scene.selected_object)
	{
		if (keycode == XK_Up)
			object_resize(rt->scene.selected_object, RESIZE_ABS_VALUE);
		else if (keycode == XK_Down)
			object_resize(rt->scene.selected_object, -RESIZE_ABS_VALUE);
		render(rt);
	}
	else if (rt->scene.expanded_legend == TRANSFORM)
	{
		t_vec3	*center;
		if (rt->scene.selected_object->type == SPHERE)
			center = &rt->scene.selected_object->data.sp.center;
		else if (rt->scene.selected_object->type == CYLINDER)
			center = &rt->scene.selected_object->data.cy.center;
		else if (rt->scene.selected_object->type == TORUS)
			center = &rt->scene.selected_object->data.to.coords;
		else if (rt->scene.selected_object->type == CONE)
			center = &rt->scene.selected_object->data.co.center;
		else if (rt->scene.selected_object->type == PLANE)
			center = &rt->scene.selected_object->data.pl.point;
		else
			return (-1);

		if (keycode == XK_Up)
			object_translate(&center->y, TRANSL_ABS_VALUE);
		else if (keycode == XK_Down)	
			object_translate(&center->y, -TRANSL_ABS_VALUE);
		else if (keycode == XK_Right)	
			object_translate(&center->x, TRANSL_ABS_VALUE);
		else if (keycode == XK_Left)	
			object_translate(&center->x, -TRANSL_ABS_VALUE);
		else if (keycode == XK_x)
			object_translate(&center->z, TRANSL_ABS_VALUE);
		else if (keycode == XK_z)
			object_translate(&center->z, -TRANSL_ABS_VALUE);
		else
			return (0);
		render(rt);
	}
	else if (rt->scene.expanded_legend == ROTATE && rt->scene.selected_object)
	{
		if (keycode == XK_Up)
			object_rotate(rt->scene.selected_object, 'x', ROTATE_ABS_VALUE);
		else if (keycode == XK_Down)
			object_rotate(rt->scene.selected_object, 'x', -ROTATE_ABS_VALUE);
		else if (keycode == XK_Right)
			object_rotate(rt->scene.selected_object, 'y', ROTATE_ABS_VALUE);
		else if (keycode == XK_Left)
			object_rotate(rt->scene.selected_object, 'y', -ROTATE_ABS_VALUE);
		else if (keycode == XK_d)
			object_rotate(rt->scene.selected_object, 'z', ROTATE_ABS_VALUE);
		else if (keycode == XK_a)
			object_rotate(rt->scene.selected_object, 'z', -ROTATE_ABS_VALUE);
		render(rt);
	}
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
