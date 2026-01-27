/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:30:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/27 17:30:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include "../libft/headers/libft.h"
#include "constants.h"
#include "structures.h"
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

/* Parser Utils */
double ft_atof(const char *str);
int parse_vec3(const char *str, t_vec3 *vec);
int parse_color(const char *str, t_color *color);
int parse_double(const char *str, double *value);
int parse_int(const char *str, int *value);
void free_split(char **split);

/* Element Parsers */
int parse_ambient(char *line, t_scene *scene);
int parse_camera(char *line, t_scene *scene);
int parse_light(char *line, t_scene *scene);
int parse_sphere(char *line, t_scene *scene);
int parse_plane(char *line, t_scene *scene);
int parse_cylinder(char *line, t_scene *scene);

/* Main Parser */
int parse_scene_file(const char *filename, t_scene *scene);

/* Scene Utils */
void init_scene(t_scene *scene);
void cleanup_scene(t_scene *scene);
t_object *create_object(int type, void *data);
void add_object(t_scene *scene, t_object *obj);

/* Error Handling */
void exit_error(const char *message);
void print_error(const char *message);

/* Debug Functions */
void debug_print_vec3(const char *name, t_vec3 vec);
void debug_print_color(const char *name, t_color color);
void debug_print_ambient(t_ambient ambient);
void debug_print_camera(t_camera camera);
void debug_print_light(t_light light);
void debug_print_sphere(t_sphere sphere);
void debug_print_plane(t_plane plane);
void debug_print_cylinder(t_cylinder cylinder);
void debug_print_scene(t_scene scene);

#endif
