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

static const double	g_resize_abs_value = (double)WIN_WIDTH / (double)384;
static const double	g_rotate_abs_value = (double)WIN_WIDTH / (double)384;
static const double	g_transl_abs_value = (double)WIN_WIDTH / (double)384;

static void	do_translate(t_vec3 *c, int keycode, t_minirt *rt)
{
	if (keycode == XK_Up)
		object_translate(&c->y, g_transl_abs_value);
	else if (keycode == XK_Down)
		object_translate(&c->y, -g_transl_abs_value);
	else if (keycode == XK_Right)
		object_translate(&c->x, g_transl_abs_value);
	else if (keycode == XK_Left)
		object_translate(&c->x, -g_transl_abs_value);
	else if (keycode == XK_x)
		object_translate(&c->z, g_transl_abs_value);
	else if (keycode == XK_z)
		object_translate(&c->z, -g_transl_abs_value);
	else
		return ;
	render(rt);
}

static void	handle_object_transform(t_minirt *rt, int keycode)
{
	t_vec3		*c;
	t_object	*o;

	o = rt->scene.selected_object;
	c = NULL;
	if (o->type == SPHERE)
		c = &o->data.sp.center;
	else if (o->type == CYLINDER)
		c = &o->data.cy.center;
	else if (o->type == TORUS)
		c = &o->data.to.coords;
	else if (o->type == CONE)
		c = &o->data.co.center;
	else if (o->type == PLANE)
		c = &o->data.pl.point;
	if (!c)
		return ;
	do_translate(c, keycode, rt);
}

static void	handle_scene_transform(t_minirt *rt, int keycode)
{
	t_vec3	*point;

	if (rt->scene.focused_right_legend == CAMERA)
		point = &rt->scene.camera.view_point;
	else
		point = &rt->scene.light.light_point;
	do_translate(point, keycode, rt);
}

static void	handle_rotate(t_minirt *rt, int keycode)
{
	t_object	*obj;

	obj = rt->scene.selected_object;
	if (keycode == XK_Up)
		object_rotate(obj, 'x', g_rotate_abs_value);
	else if (keycode == XK_Down)
		object_rotate(obj, 'x', -g_rotate_abs_value);
	else if (keycode == XK_Right)
		object_rotate(obj, 'y', g_rotate_abs_value);
	else if (keycode == XK_Left)
		object_rotate(obj, 'y', -g_rotate_abs_value);
	else if (keycode == XK_d)
		object_rotate(obj, 'z', g_rotate_abs_value);
	else if (keycode == XK_a)
		object_rotate(obj, 'z', -g_rotate_abs_value);
	else
		return ;
	render(rt);
}

void	dispatch_focus(t_minirt *rt, int keycode)
{
	if (rt->scene.focused_op_legend == RESIZE && rt->scene.selected_object)
	{
		if (keycode == XK_Up)
			object_resize(rt->scene.selected_object, g_resize_abs_value);
		else if (keycode == XK_Down)
			object_resize(rt->scene.selected_object, -g_resize_abs_value);
		else
			return ;
		render(rt);
	}
	else if (rt->scene.focused_op_legend == ROTATE && rt->scene.selected_object)
		handle_rotate(rt, keycode);
	else if (rt->scene.focused_op_legend == TRANSFORM
		&& rt->scene.selected_object)
		handle_object_transform(rt, keycode);
	else if (rt->scene.focused_op_legend == TRANSFORM
		&& rt->scene.focused_right_legend != NO_LEGEND)
		handle_scene_transform(rt, keycode);
}
