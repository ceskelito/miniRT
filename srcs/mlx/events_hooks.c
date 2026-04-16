/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:30:13 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/16 12:10:43 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "legend.h"
#include <X11/keysym.h>

static const double g_resize_abs_value = (double) WIN_WIDTH / (double) 384;
static const double g_rotate_abs_value = (double) WIN_WIDTH / (double) 384;
static const double g_transl_abs_value = (double) WIN_WIDTH / (double) 384;

int handle_mouse_events(int button, int x, int y, t_minirt *rt)
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

/***** END OF MOUSE OBJECT SELECTION *****/

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

int	handle_keypress(int keycode, t_minirt *rt)
{
	if (keycode == XK_Escape)
		rt_close_program(rt);

	if (keycode == XK_l)
	{
		toggle_right_legend(rt, LIGHTS);
		render(rt);
		return (0);
	}
	if (keycode == XK_c)
	{
		toggle_right_legend(rt, CAMERA);
		render(rt);
		return (0);
	}
	if (keycode == XK_r)
	{
		render(rt);
		return (0);
	}

	if ((keycode == XK_1 || keycode == XK_2 || keycode == XK_3) && rt->scene.selected_object != NULL)
	{
		if (keycode == XK_1)
			rt->scene.focused_op_legend = RESIZE;
		else if (keycode == XK_2)
			rt->scene.focused_op_legend = TRANSFORM;
		else if (keycode == XK_3)
			rt->scene.focused_op_legend = ROTATE;
		else
			return (0);
		print_operations_legend(rt);
		return (0);
	}
	if (rt->scene.focused_op_legend == RESIZE && rt->scene.selected_object)
	{
		if (keycode == XK_Up)
			object_resize(rt->scene.selected_object, g_resize_abs_value);
		else if (keycode == XK_Down)
			object_resize(rt->scene.selected_object, -g_resize_abs_value);
		else
			return (0);
		render(rt);
	}
	else if (rt->scene.focused_op_legend == TRANSFORM && rt->scene.selected_object)
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
			object_translate(&center->y, g_transl_abs_value);
		else if (keycode == XK_Down)	
			object_translate(&center->y, -g_transl_abs_value);
		else if (keycode == XK_Right)	
			object_translate(&center->x, g_transl_abs_value);
		else if (keycode == XK_Left)	
			object_translate(&center->x, -g_transl_abs_value);
		else if (keycode == XK_x)
			object_translate(&center->z, g_transl_abs_value);
		else if (keycode == XK_z)
			object_translate(&center->z, -g_transl_abs_value);
		else
			return (0);
		render(rt);
	}
	else if (rt->scene.focused_op_legend == ROTATE && rt->scene.selected_object)
	{
		if (keycode == XK_Up)
			object_rotate(rt->scene.selected_object, 'x', g_rotate_abs_value);
		else if (keycode == XK_Down)
			object_rotate(rt->scene.selected_object, 'x', -g_rotate_abs_value);
		else if (keycode == XK_Right)
			object_rotate(rt->scene.selected_object, 'y', g_rotate_abs_value);
		else if (keycode == XK_Left)
			object_rotate(rt->scene.selected_object, 'y', -g_rotate_abs_value);
		else if (keycode == XK_d)
			object_rotate(rt->scene.selected_object, 'z', g_rotate_abs_value);
		else if (keycode == XK_a)
			object_rotate(rt->scene.selected_object, 'z', -g_rotate_abs_value);
		else
			return (0);
		render(rt);
	}
	else if (rt->scene.focused_op_legend == TRANSFORM
		&& rt->scene.focused_right_legend != NO_LEGEND)
	{
		t_vec3	*point;

		if (rt->scene.focused_right_legend == CAMERA)
			point = &rt->scene.camera.view_point;
		else
			point = &rt->scene.light.light_point;
		if (keycode == XK_Up)
			object_translate(&point->y, g_transl_abs_value);
		else if (keycode == XK_Down)
			object_translate(&point->y, -g_transl_abs_value);
		else if (keycode == XK_Right)
			object_translate(&point->x, g_transl_abs_value);
		else if (keycode == XK_Left)
			object_translate(&point->x, -g_transl_abs_value);
		else if (keycode == XK_x)
			object_translate(&point->z, g_transl_abs_value);
		else if (keycode == XK_z)
			object_translate(&point->z, -g_transl_abs_value);
		else
			return (0);
		render(rt);
	}
	else
		return (0);
	return (0);
}
