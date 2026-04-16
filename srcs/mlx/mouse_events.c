/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 12:00:00 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/16 12:00:00 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "legend.h"
#include <X11/keysym.h>

static void	toggle_right_legend(t_minirt *rt, int which)
{
	if (rt->scene.focused_right_legend == which)
	{
		rt->scene.focused_right_legend = NO_LEGEND;
		rt->scene.focused_op_legend = NO_LEGEND;
	}
	else
	{
		rt->scene.focused_right_legend = which;
		rt->scene.selected_object = NULL;
		rt->scene.focused_op_legend = TRANSFORM;
	}
}

int	handle_mouse_events(int button, int x, int y, t_minirt *rt)
{
	if (button == MOUSE_LEFT)
	{
		rt->scene.selected_object = get_selected_object(rt, x, y);
		if (rt->scene.selected_object)
		{
			if (rt->scene.focused_op_legend == NO_LEGEND)
				rt->scene.focused_op_legend = RESIZE;
		}
		else
			rt->scene.focused_op_legend = NO_LEGEND;
		render(rt);
	}
	return (0);
}

int	handle_keypress(int keycode, t_minirt *rt)
{
	if (keycode == XK_Escape)
		rt_close_program(rt);
	if (keycode == XK_l)
		return (toggle_right_legend(rt, LIGHTS), render(rt), 0);
	if (keycode == XK_c)
		return (toggle_right_legend(rt, CAMERA), render(rt), 0);
	if (keycode == XK_r)
		return (render(rt), 0);
	if ((keycode == XK_1 || keycode == XK_2 || keycode == XK_3)
		&& rt->scene.selected_object)
	{
		rt->scene.focused_op_legend = keycode - XK_0 - 1;
		print_operations_legend(rt);
		return (0);
	}
	dispatch_focus(rt, keycode);
	return (0);
}
