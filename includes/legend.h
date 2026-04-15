/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legend.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:19:24 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/15 10:51:29 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEGEND_H
# define LEGEND_H

# define CHAR_HEIGHT	16	// pixels
# define CHAR_WIDTH		8	// pixels

// # define MENU_ITEMS 3

# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define GREEN 0x228B22

enum { X = 10, Y = 20 };

// Operations Legends
enum { RESIZE = 0, TRANSFORM = 1, ROTATE = 2};
// Right Legends
enum { CAMERA = 0, LIGHTS = 1};
// General
enum { NO_LEGEND = -1};

typedef struct s_minirt	t_minirt;
typedef struct s_mlx	t_mlx;

typedef struct s_legend_colors
{
	int background;
	int foreground;
} t_legend_colors;

typedef struct s_legends
{
	int start_x;
	int start_y;

	t_legend_colors colors_focused;
	t_legend_colors colors_ignored;

	const char **legends[];

} t_legends;

int	print_operations_legend(t_minirt *rt);
int print_camera_legend(t_minirt *rt);
int	count_elem(const char *legend[]);
int print_background(t_mlx *mlx, const char *legend[], int b_color, int f_color, int x, int y);
void print_text(t_mlx *mlx, const char *legend[], int color, int x, int y);

#endif
