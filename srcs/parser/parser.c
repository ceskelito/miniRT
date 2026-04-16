/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:00:00 by antigravit        #+#    #+#             */
/*   Updated: 2026/04/07 10:42:30 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include "parser.h"

void	free_tokens(char **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

static char	*dispatch_shapes(char **tokens, t_scene *scene)
{
	if (ft_strncmp(tokens[0], "sp", 3) == 0)
		return (parse_sphere(tokens, &scene->objects));
	if (ft_strncmp(tokens[0], "pl", 3) == 0)
		return (parse_plane(tokens, &scene->objects));
	if (ft_strncmp(tokens[0], "cy", 3) == 0)
		return (parse_cylinder(tokens, &scene->objects));
	if (ft_strncmp(tokens[0], "co", 3) == 0)
		return (parse_cone(tokens, &scene->objects));
	if (ft_strncmp(tokens[0], "to", 3) == 0)
		return (parse_torus(tokens, &scene->objects));
	return ("Unknown identifier");
}

static char	*dispatch_line(char **tokens, t_scene *scene)
{
	if (!tokens || !tokens[0] || tokens[0][0] == '#')
		return (NULL);
	if (ft_strncmp(tokens[0], "A", 2) == 0)
		return (parse_ambient(tokens, &scene->ambient));
	if (ft_strncmp(tokens[0], "C", 2) == 0)
		return (parse_camera(tokens, &scene->camera));
	if (ft_strncmp(tokens[0], "L", 2) == 0)
		return (parse_light(tokens, &scene->light));
	return (dispatch_shapes(tokens, scene));
}

static void	process_line(char *line, t_minirt *rt)
{
	char	**tokens;
	char	*trimmed;
	char	*err;

	if (!line)
		return ;
	trimmed = ft_strtrim(line, "\n");
	if (!trimmed)
		return ;
	if (ft_strlen(trimmed) == 0)
		return (free(trimmed));
	tokens = ft_split(trimmed, ' ');
	free(trimmed);
	if (!tokens)
	{
		free(line);
		exit_error(strerror(errno), rt);
	}
	err = dispatch_line(tokens, &rt->scene);
	free_tokens(tokens);
	if (err)
	{
		free(line);
		exit_error(err, rt);
	}
}

void	parse_scene(char *filename, t_minirt *rt)
{
	int		fd;
	char	*line;

	if (ft_strncmp(filename + ft_strlen(filename) - 3, ".rt", 3) != 0)
		exit_error("File must have .rt extension", rt);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error(strerror(errno), rt);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		process_line(line, rt);
		free(line);
	}
	close(fd);
}
