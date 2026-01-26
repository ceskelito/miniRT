/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:00:00 by antigravit        #+#    #+#             */
/*   Updated: 2026/01/26 12:00:00 by antigravit       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "../libft/headers/get_next_line.h"
#include "../libft/headers/libft.h"
#include "minirt.h"

/*
** parser.c
*/
void parse_scene(char *filename, t_minirt *rt);

/*
** parse_utils.c
*/
double ft_atof(char *str);
int parse_vec3(char *str, t_vec3 *vec);
int parse_color(char *str, t_color *color);
int is_whitespace(char c);

/*
** parse_elements.c
*/
void parse_ambient(char **tokens, t_minirt *rt);
void parse_camera(char **tokens, t_minirt *rt);
void parse_light(char **tokens, t_minirt *rt);

/*
** parse_shapes.c
*/
void parse_sphere(char **tokens, t_minirt *rt);
void parse_plane(char **tokens, t_minirt *rt);
void parse_cylinder(char **tokens, t_minirt *rt);

/*
** debug.c
*/
void print_scene(t_minirt *rt);

/*
** cleanup.c
*/
void free_scene(t_minirt *rt);
void exit_error(char *msg, t_minirt *rt);
void free_tokens(char **tokens);

#endif
