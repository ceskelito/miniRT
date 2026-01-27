/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:30:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/27 17:30:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int parse_line(char *line, t_scene *scene) {
	if (!line || !*line || *line == '\n')
		return (1);
	if (line[0] == 'A' && line[1] == ' ')
		return (parse_ambient(line, scene));
	else if (line[0] == 'C' && line[1] == ' ')
		return (parse_camera(line, scene));
	else if (line[0] == 'L' && line[1] == ' ')
		return (parse_light(line, scene));
	else if (line[0] == 's' && line[1] == 'p' && line[2] == ' ')
		return (parse_sphere(line, scene));
	else if (line[0] == 'p' && line[1] == 'l' && line[2] == ' ')
		return (parse_plane(line, scene));
	else if (line[0] == 'c' && line[1] == 'y' && line[2] == ' ')
		return (parse_cylinder(line, scene));
	else
		return (print_error(ERROR_FILE_FORMAT), 0);
}

static int validate_required(t_scene *scene) {
	if (!scene->ambient.is_set)
		return (print_error(ERROR_MISSING_ELEMENT), 0);
	if (!scene->camera.is_set)
		return (print_error(ERROR_MISSING_ELEMENT), 0);
	if (!scene->light.is_set)
		return (print_error(ERROR_MISSING_ELEMENT), 0);
	return (1);
}

static int read_and_parse(int fd, t_scene *scene) {
	char *line;
	int result;

	line = get_next_line(fd);
	while (line) {
		result = parse_line(line, scene);
		free(line);
		if (!result)
			return (0);
		line = get_next_line(fd);
	}
	return (1);
}

int parse_scene_file(const char *filename, t_scene *scene) {
	int fd;
	int result;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (print_error(ERROR_FILE_OPEN), 0);
	init_scene(scene);
	result = read_and_parse(fd, scene);
	close(fd);
	if (!result)
		return (cleanup_scene(scene), 0);
	if (!validate_required(scene))
		return (cleanup_scene(scene), 0);
	return (1);
}
