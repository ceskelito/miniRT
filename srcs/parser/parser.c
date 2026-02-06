/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:00:00 by antigravit        #+#    #+#             */
/*   Updated: 2026/02/06 11:10:20 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include "parser.h"

void free_tokens(char **tokens) {
	int i;

	if (!tokens)
		return;
	i = 0;
	while (tokens[i]) {
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

static void dispatch_line(char **tokens, t_minirt *rt) {
	if (!tokens || !tokens[0])
		return;
	if (ft_strncmp(tokens[0], "A", 2) == 0)
		parse_ambient(tokens, rt);
	else if (ft_strncmp(tokens[0], "C", 2) == 0)
		parse_camera(tokens, rt);
	else if (ft_strncmp(tokens[0], "L", 2) == 0)
		parse_light(tokens, rt);
	else if (ft_strncmp(tokens[0], "sp", 3) == 0)
		parse_sphere(tokens, rt);
	else if (ft_strncmp(tokens[0], "pl", 3) == 0)
		parse_plane(tokens, rt);
	else if (ft_strncmp(tokens[0], "cy", 3) == 0)
		parse_cylinder(tokens, rt);
	else if (tokens[0][0] == '#')
		return;
	else
		exit_error("Unknown identifier", rt);
}

static void process_line(char *line, t_minirt *rt) {
	char **tokens;
	char *trimmed;

	if (!line)
		return;
	trimmed = ft_strtrim(line, "\n");
	if (!trimmed)
		return; // Empty line or alloc fail handled naturally
	if (ft_strlen(trimmed) == 0) {
		free(trimmed);
		return;
	}
	tokens = ft_split(trimmed, ' ');
	free(trimmed);
	if (!tokens)
		exit_error("Memory allocation failed", rt);
	if (tokens[0])
		dispatch_line(tokens, rt);
	free_tokens(tokens);
}

void parse_scene(char *filename, t_minirt *rt) {
	int fd;
	char *line;

	if (ft_strncmp(filename + ft_strlen(filename) - 3, ".rt", 3) != 0)
		exit_error("File must have .rt extension", rt);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error("Cannot open file", rt);
	while (1) {
		line = get_next_line(fd);
		if (!line)
			break;
		process_line(line, rt);
		free(line);
	}
	close(fd);
}
