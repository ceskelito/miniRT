/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:00:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/23 00:00:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>

/* Release a NULL-terminated split array. */
void	free_split(char **parts)
{
	int	i;

	if (parts == NULL)
		return ;
	i = 0;
	while (parts[i] != NULL)
	{
		free(parts[i]);
		i = i + 1;
	}
	free(parts);
}

/* Parse a single color component in range 0..255. */
static int	parse_color_component(const char *str, int *out)
{
	char	*end;
	long	value;

	if (str == NULL || out == NULL)
		return (0);
	end = NULL;
	value = strtol(str, &end, 10);
	if (end == str || *end != '\0' || value < 0 || value > 255)
		return (0);
	*out = (int)value;
	return (1);
}

/* Parse a floating point number with full validation. */
int	parse_double(const char *str, double *out)
{
	char	*end;
	double	value;

	if (str == NULL || out == NULL)
		return (0);
	end = NULL;
	value = strtod(str, &end);
	if (end == str || *end != '\0')
		return (0);
	*out = value;
	return (1);
}

/* Parse a vector in the form "x,y,z". */
int	parse_vec3(const char *token, t_vec3 *out)
{
	char	**parts;

	if (token == NULL || out == NULL)
		return (0);
	parts = ft_split(token, ',');
	if (parts == NULL)
		return (0);
	if (!parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		free_split(parts);
		return (0);
	}
	if (!parse_double(parts[0], &out->x)
		|| !parse_double(parts[1], &out->y)
		|| !parse_double(parts[2], &out->z))
	{
		free_split(parts);
		return (0);
	}
	free_split(parts);
	return (1);
}

/* Parse a color in the form "r,g,b". */
int	parse_color(const char *token, t_color *out)
{
	char	**parts;

	if (token == NULL || out == NULL)
		return (0);
	parts = ft_split(token, ',');
	if (parts == NULL)
		return (0);
	if (!parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		free_split(parts);
		return (0);
	}
	if (!parse_color_component(parts[0], &out->r)
		|| !parse_color_component(parts[1], &out->g)
		|| !parse_color_component(parts[2], &out->b))
	{
		free_split(parts);
		return (0);
	}
	free_split(parts);
	return (1);
}
