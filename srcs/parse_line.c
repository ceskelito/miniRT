/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:00:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/23 00:00:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>

/* Parse ambient light line. */
extern t_parse_error	parse_ambient_line(char **parts, t_scene *scene);

/* Parse camera line. */
extern t_parse_error	parse_camera_line(char **parts, t_scene *scene);

/* Parse light line. */
extern t_parse_error	parse_light_line(char **parts, t_scene *scene);

/* Parse sphere line. */
extern t_parse_error	parse_sphere_line(char **parts, t_scene *scene);

/* Parse plane line. */
extern t_parse_error	parse_plane_line(char **parts, t_scene *scene);

/* Parse cylinder line. */
extern t_parse_error	parse_cylinder_line(char **parts, t_scene *scene);

/* Normalize whitespace for a line and trim edges. */
static char	*normalize_line(const char *line)
{
	char	*dup;
	char	*trimmed;
	size_t	i;

	if (line == NULL)
		return (NULL);
	dup = ft_strdup(line);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (dup[i] != '\0')
	{
		if (dup[i] == '\t')
			dup[i] = ' ';
		i = i + 1;
	}
	trimmed = ft_strtrim(dup, " \t\n\r");
	free(dup);
	return (trimmed);
}

/* Identify the token for the first word of a line. */
static t_token	detect_token(const char *word)
{
	if (word == NULL)
		return (TOK_EMPTY);
	if (ft_strncmp(word, "A", 2) == 0)
		return (TOK_AMBIENT);
	if (ft_strncmp(word, "C", 2) == 0)
		return (TOK_CAMERA);
	if (ft_strncmp(word, "L", 2) == 0)
		return (TOK_LIGHT);
	if (ft_strncmp(word, "sp", 3) == 0)
		return (TOK_SPHERE);
	if (ft_strncmp(word, "pl", 3) == 0)
		return (TOK_PLANE);
	if (ft_strncmp(word, "cy", 3) == 0)
		return (TOK_CYLINDER);
	return (TOK_UNKNOWN);
}

/* Dispatch parsing based on the first token. */
static t_parse_error	dispatch_line(char **parts, t_parse_state *state)
{
	t_token	token;

	token = detect_token(parts[0]);
	if (token == TOK_AMBIENT)
		return (parse_ambient_line(parts, state->scene));
	if (token == TOK_CAMERA)
		return (parse_camera_line(parts, state->scene));
	if (token == TOK_LIGHT)
		return (parse_light_line(parts, state->scene));
	if (token == TOK_SPHERE)
		return (parse_sphere_line(parts, state->scene));
	if (token == TOK_PLANE)
		return (parse_plane_line(parts, state->scene));
	if (token == TOK_CYLINDER)
		return (parse_cylinder_line(parts, state->scene));
	return (PARSE_ERR_SYNTAX);
}

/* Parse a single .rt line into the scene. */
t_parse_error	parse_line(const char *line, t_parse_state *state)
{
	char			*trimmed;
	char			**parts;
	t_parse_error	err;

	trimmed = normalize_line(line);
	if (trimmed == NULL)
		return (PARSE_ERR_MEM);
	if (trimmed[0] == '\0')
	{
		free(trimmed);
		return (PARSE_OK);
	}
	parts = ft_split(trimmed, ' ');
	free(trimmed);
	if (parts == NULL)
		return (PARSE_ERR_MEM);
	err = dispatch_line(parts, state);
	free_split(parts);
	return (err);
}
