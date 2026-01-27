/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:30:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/27 17:30:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct s_vec3 {
	double x;
	double y;
	double z;
} t_vec3;

typedef struct s_color {
	int r;
	int g;
	int b;
} t_color;

typedef struct s_ambient {
	double ratio;
	t_color color;
	int is_set;
} t_ambient;

typedef struct s_camera {
	t_vec3 position;
	t_vec3 orientation;
	int fov;
	int is_set;
} t_camera;

typedef struct s_light {
	t_vec3 position;
	double brightness;
	t_color color;
	int is_set;
} t_light;

typedef struct s_sphere {
	t_vec3 center;
	double diameter;
	t_color color;
} t_sphere;

typedef struct s_plane {
	t_vec3 point;
	t_vec3 normal;
	t_color color;
} t_plane;

typedef struct s_cylinder {
	t_vec3 center;
	t_vec3 axis;
	double diameter;
	double height;
	t_color color;
} t_cylinder;

typedef struct s_object {
	int type;
	void *data;
	struct s_object *next;
} t_object;

typedef struct s_scene {
	t_ambient ambient;
	t_camera camera;
	t_light light;
	t_object *objects;
} t_scene;

#endif
