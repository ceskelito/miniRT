/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:00:00 by antigravit        #+#    #+#             */
/*   Updated: 2026/04/07 10:35:49 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

static inline bool	is_normalized(t_vec3 *v)
{
	return ((v->x >= -1 && v->x <= 1)
		&& (v->y >= -1 && v->y <= 1)
		&& (v->z >= -1 && v->z <= 1));
}

char	*parse_ambient(char **tokens, t_ambient *ambient)
{
	static int	count = 0;

	if (count++ > 0)
		return ("Multiple Ambient (A) defined");
	if (!tokens[1] || !tokens[2] || tokens[3])
		return ("Invalid Ambient format: A <ratio> <R,G,B>");
	ambient->ratio = ft_atof(tokens[1]);
	if (ambient->ratio < 0.0 || ambient->ratio > 1.0)
		return ("Ambient ratio must be [0.0, 1.0]");
	if (!parse_color(tokens[2], &ambient->color))
		return ("Invalid Ambient color");
	return (NULL);
}

char	*parse_camera(char **tokens, t_camera *camera)
{
	static int	count = 0;

	if (count++ > 0)
		return ("Multiple Cameras (C) defined");
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return ("Invalid Camera format");
	if (!parse_vec3(tokens[1], &camera->view_point))
		return ("Invalid Camera view point");
	if (!parse_vec3(tokens[2], &camera->orientation)
		|| !is_normalized(&camera->orientation))
		return ("Invalid Camera orientation");
	camera->fov = ft_atoi(tokens[3]);
	if (camera->fov < 0 || camera->fov > 180)
		return ("Camera FOV must be [0, 180]");
	return (NULL);
}

char	*parse_light(char **tokens, t_light *light)
{
	static int	count = 0;

	if (count++ > 0)
		return ("Multiple Lights (L) defined");
	if (!tokens[1] || !tokens[2] || !tokens[3])
		return ("Invalid Light format");
	if (!parse_vec3(tokens[1], &light->light_point))
		return ("Invalid Light point");
	light->brightness_ratio = ft_atof(tokens[2]);
	if (light->brightness_ratio < 0.0
		|| light->brightness_ratio > 1.0)
		return ("Light brightness must be [0.0, 1.0]");
	if (tokens[3])
	{
		if (!parse_color(tokens[3], &light->color))
			return ("Invalid Light color");
	}
	else
	{
		light->color.r = 255;
		light->color.g = 255;
		light->color.b = 255;
	}
	return (NULL);
}
