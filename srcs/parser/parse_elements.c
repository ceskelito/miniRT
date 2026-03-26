/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:00:00 by antigravit        #+#    #+#             */
/*   Updated: 2026/02/06 16:56:40 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

static inline bool	is_normalized(t_vec3 *v) {
	return ((v->x >= -1 && v->x <= 1) &&
			(v->y >= -1 && v->y <= 1) &&
			(v->z >= -1 && v->z <= 1));
}

void	parse_ambient(char **tokens, t_minirt *rt)
{
	static int	count = 0;

	if (count++ > 0)
		exit_error("Multiple Ambient (A) defined", rt);
	if (!tokens[1] || !tokens[2] || tokens[3])
		exit_error("Invalid Ambient format: A <ratio> <R,G,B>", rt);
	rt->scene.ambient.ratio = ft_atof(tokens[1]);
	if (rt->scene.ambient.ratio < 0.0 || rt->scene.ambient.ratio > 1.0)
		exit_error("Ambient ratio must be [0.0, 1.0]", rt);
	if (!parse_color(tokens[2], &rt->scene.ambient.color))
		exit_error("Invalid Ambient color", rt);
}

void	parse_camera(char **tokens, t_minirt *rt)
{
	static int	count = 0;

	if (count++ > 0)
		exit_error("Multiple Cameras (C) defined", rt);
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		exit_error("Invalid Camera format", rt);
	if (!parse_vec3(tokens[1], &rt->scene.camera.view_point))
		exit_error("Invalid Camera view point", rt);
	if (!parse_vec3(tokens[2], &rt->scene.camera.orientation) ||
		!is_normalized(&rt->scene.camera.orientation))
		exit_error("Invalid Camera orientation", rt);
	rt->scene.camera.fov = ft_atoi(tokens[3]);
	if (rt->scene.camera.fov < 0 || rt->scene.camera.fov > 180)
		exit_error("Camera FOV must be [0, 180]", rt);
}

void	parse_light(char **tokens, t_minirt *rt)
{
	static int	count = 0;

	if (count++ > 0)
		exit_error("Multiple Lights (L) defined", rt);
	if (!tokens[1] || !tokens[2] || !tokens[3])
		exit_error("Invalid Light format", rt);
	if (!parse_vec3(tokens[1], &rt->scene.light.light_point))
		exit_error("Invalid Light point", rt);
	rt->scene.light.brightness_ratio = ft_atof(tokens[2]);
	if (rt->scene.light.brightness_ratio < 0.0
		|| rt->scene.light.brightness_ratio > 1.0)
		exit_error("Light brightness must be [0.0, 1.0]", rt);
	if (tokens[3])
	{
		if (!parse_color(tokens[3], &rt->scene.light.color))
			exit_error("Invalid Light color", rt);
	}
	else
	{
		rt->scene.light.color.r = 255;
		rt->scene.light.color.g = 255;
		rt->scene.light.color.b = 255;
	}
}
