/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legends_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:27:47 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/15 10:56:16 by rceschel         ###   ########.fr       */
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

int print_background(t_mlx *mlx, const char *legend[], int b_color, int f_color, int x, int y)
{
	t_img	background;
	int		width;
	int		height;

	width = CHAR_WIDTH * 22;
	height = CHAR_HEIGHT * (count_elem(legend) + 2);
	img_create(mlx->ptr, &background, width, height);
	img_set_background(&background, b_color);
	img_add_frame(&background, f_color);
	mlx_put_image_to_window(mlx->ptr, mlx->win, background.img, x, y);
	mlx_destroy_image(mlx->ptr, background.img);
	return (height);
}

void print_text(t_mlx *mlx, const char *legend[], int color, int x, int y)
{
	int i;
	int n;

	i = 0;
	n = count_elem(legend);
	while (i < n)
	{
		mlx_string_put(mlx->ptr, mlx->win, x, y, color, (char *)legend[i]);
		if (i == 0)
			x += 10;
		y += CHAR_HEIGHT;
		i++;
	}
}

