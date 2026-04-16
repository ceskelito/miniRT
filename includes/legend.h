/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legend.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:19:24 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/16 13:43:33 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEGEND_H
# define LEGEND_H

# define CHAR_HEIGHT 16
# define CHAR_WIDTH 8

# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define GREEN 0x228B22

typedef struct s_minirt	t_minirt;
typedef struct s_mlx	t_mlx;

enum
{
	X = 10,
	Y = 20
};

enum
{
	RESIZE = 0,
	TRANSFORM = 1,
	ROTATE = 2
};

enum
{
	CAMERA = 0,
	LIGHTS = 1,
	OTHER = 2
};

enum
{
	NO_LEGEND = -1
};

typedef struct s_legend_colors
{
	int					background;
	int					foreground;
}						t_legend_colors;

typedef struct s_legends
{
	int					start_x;
	int					start_y;
	int					*focused_legend;
	t_legend_colors		colors_focused;
	t_legend_colors		colors_ignored;
	const char			***legends;
}						t_legends;

int						print_operations_legend(t_minirt *rt);
int						print_camera_legend(t_minirt *rt);
int						count_elem(const char *legend[]);
int						print_background(t_mlx *mlx, const t_legends *set,
							int index, int y);
void					print_text(t_mlx *mlx, const t_legends *set,
							int index, int pos[2]);

#endif
