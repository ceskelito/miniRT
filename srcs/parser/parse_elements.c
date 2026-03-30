/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:00:00 by antigravit        #+#    #+#             */
/*   Updated: 2026/03/30 15:47:17 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

static inline bool	is_normalized(t_vec3 *v) {
	return ((v->x >= -1 && v->x <= 1) &&
			(v->y >= -1 && v->y <= 1) &&
			(v->z >= -1 && v->z <= 1));
}

char	*parse_ambient(char **tokens, t_minirt *rt)
{
	static int	count = 0;

	if (count++ > 0)
		return ("Multiple Ambient (A) defined");
	if (!tokens[1] || !tokens[2] || tokens[3])
		return ("Invalid Ambient format: A <ratio> <R,G,B>");
	rt->scene.ambient.ratio = ft_atof(tokens[1]);
	if (rt->scene.ambient.ratio < 0.0 || rt->scene.ambient.ratio > 1.0)
		return ("Ambient ratio must be [0.0, 1.0]");
	if (!parse_color(tokens[2], &rt->scene.ambient.color))
		return ("Invalid Ambient color");
	return (NULL);
}

char	*parse_camera(char **tokens, t_minirt *rt)
{
	static int	count = 0;

	if (count++ > 0)
		return ("Multiple Cameras (C) defined");
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return ("Invalid Camera format");
	if (!parse_vec3(tokens[1], &rt->scene.camera.view_point))
		return ("Invalid Camera view point");
	if (!parse_vec3(tokens[2], &rt->scene.camera.orientation) ||
		!is_normalized(&rt->scene.camera.orientation))
		return ("Invalid Camera orientation");
	rt->scene.camera.fov = ft_atoi(tokens[3]);
	if (rt->scene.camera.fov < 0 || rt->scene.camera.fov > 180)
		return ("Camera FOV must be [0, 180]");
	return (NULL);
}

char	*parse_light(char **tokens, t_minirt *rt)
{
	static int	count = 0;

	if (count++ > 0)
		return ("Multiple Lights (L) defined");
	if (!tokens[1] || !tokens[2] || !tokens[3])
		return ("Invalid Light format");
	if (!parse_vec3(tokens[1], &rt->scene.light.light_point))
		return ("Invalid Light point");
	rt->scene.light.brightness_ratio = ft_atof(tokens[2]);
	if (rt->scene.light.brightness_ratio < 0.0
		|| rt->scene.light.brightness_ratio > 1.0)
		return ("Light brightness must be [0.0, 1.0]");
	if (tokens[3])
	{
		if (!parse_color(tokens[3], &rt->scene.light.color))
			return ("Invalid Light color");
	}
	else
	{
		rt->scene.light.color.r = 255;
		rt->scene.light.color.g = 255;
		rt->scene.light.color.b = 255;
	}
	return (NULL);
}
