/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:00:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/23 00:00:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

/* Parse a single line into scene data. */
extern t_parse_error	parse_line(const char *line, t_parse_state *state);

/* Read all lines from the file descriptor and parse them. */
static t_parse_error	parse_lines(int fd, t_parse_state *state)
{
	char			*line;
	t_parse_error	err;

	err = PARSE_OK;
	line = get_next_line(fd);
	while (line != NULL)
	{
		state->line = state->line + 1;
		err = parse_line(line, state);
		free(line);
		if (err != PARSE_OK)
			return (err);
		line = get_next_line(fd);
	}
	return (PARSE_OK);
}

/* Parse a .rt file and fill the given scene. */
t_parse_error	parse_scene(const char *path, t_scene *scene)
{
	t_parse_state	state;
	t_parse_error	err;
	int				fd;

	if (path == NULL || scene == NULL)
		return (PARSE_ERR_IO);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (PARSE_ERR_IO);
	state.path = path;
	state.line = 0;
	state.scene = scene;
	err = parse_lines(fd, &state);
	close(fd);
	return (err);
}
