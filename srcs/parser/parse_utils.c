/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:00:00 by antigravit        #+#    #+#             */
/*   Updated: 2026/02/06 11:10:14 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include "parser.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

double	ft_atof(char *str)
{
	double	res;
	double	factor;
	int		sign;
	int		i;

	i = 0;
	res = 0.0;
	factor = 1.0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (ft_isdigit(str[i]))
		res = res * 10 + (str[i++] - '0');
	if (str[i] == '.')
	{
		i++;
		while (ft_isdigit(str[i]))
		{
			res = res * 10 + (str[i++] - '0');
			factor *= 10;
		}
	}
	return (sign * res / factor);
}

int	parse_vec3(char *str, t_vec3 *vec)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split)
		return (0);
	if (!split[0] || !split[1] || !split[2] || split[3])
	{
		free_tokens(split);
		return (0);
	}
	vec->x = ft_atof(split[0]);
	vec->y = ft_atof(split[1]);
	vec->z = ft_atof(split[2]);
	free_tokens(split);
	return (1);
}

int	parse_color(char *str, t_color *color)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	split = ft_split(str, ',');
	if (!split)
		return (0);
	if (!split[0] || !split[1] || !split[2] || split[3])
	{
		free_tokens(split);
		return (0);
	}
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free_tokens(split);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	color->r = r;
	color->g = g;
	color->b = b;
	return (1);
}
