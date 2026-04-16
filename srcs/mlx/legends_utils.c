/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legends_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:27:47 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/16 13:28:50 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "legend.h"
#include "minirt.h"
#include "mlx_imglib.h"

int	count_elem(const char *legend[])
{
	int	i;

	i = 0;
	while (legend[i])
		i++;
	return (i);
}

int	print_background(t_mlx *mlx, const t_legends *set, int index, int y)
{
	t_img			background;
	int				width;
	int				height;
	t_legend_colors colors;

	if (*set->focused_legend == index)
		colors = set->colors_focused;
	else
		colors = set->colors_ignored;

	width = CHAR_WIDTH * 22;
	height = CHAR_HEIGHT * (count_elem(set->legends[index]) + 2);
	img_create(mlx->ptr, &background, width, height);
	img_set_background(&background, colors.background);
	img_add_frame(&background, colors.foreground);
	mlx_put_image_to_window(mlx->ptr, mlx->win, background.img, set->start_x, y);
	mlx_destroy_image(mlx->ptr, background.img);
	return (height);
}

void	print_text(t_mlx *mlx, const t_legends *set, int index, int x, int y)
{
	int				i;
	int 			n;
	t_legend_colors colors;

	if (*set->focused_legend == index)
		colors = set->colors_focused;
	else
		colors = set->colors_ignored;


	i = 0;
	n = count_elem(set->legends[index]);
	while (i < n)
	{
		mlx_string_put(mlx->ptr, mlx->win, x, y, colors.foreground,
			(char *)set->legends[index][i]);
		if (i == 0)
			x += 10;
		y += CHAR_HEIGHT;
		i++;
	}
}

