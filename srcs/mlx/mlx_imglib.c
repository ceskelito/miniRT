/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_imglib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:29:45 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/13 16:01:19 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_imglib.h"

int	img_get_offset(t_img *img, int x, int y)
{
	if (!img)
		return(MLX_ERROR);
	return (y * img->line_len + x * (img->bpp / 8));
}

int	img_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dest;

	if (!img || !img->addr)
		return(MLX_ERROR);
	dest = img->addr + img_get_offset(img, x, y);
	if (!dest)
		return(MLX_ERROR);
	*(unsigned int *)dest = color;
	return (0);
}

int	img_create(void *mlx, t_img *img, int img_width, int img_height)
{
	if (!mlx || !img)
		return(MLX_ERROR);
	img->img = mlx_new_image(mlx, img_width, img_height);
	if (!img->img)
		return(MLX_ERROR);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	if (!img->addr)
		return(MLX_ERROR);
	img->width = img_width;
	img->height = img_height;
	return (0);
}

int	img_set_background(t_img *img, int color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			if (img_put_pixel(img, x, y, color) == MLX_ERROR)
				return (MLX_ERROR);
			x++;
		}
		y++;
	}
	return (0);
}

void	img_add_frame(t_img *img, int color)
{
	int	x;
	int	y;

	if (!img || !img->addr)
		return ;
	x = 0;
	y = 0;
	while (x < img->width)
	{
		img_put_pixel(img, x, 0, color);
		img_put_pixel(img, x, img->height - 1, color);
		x++;
	}
	while (y < img->height)
	{
		img_put_pixel(img, 0, y, color);
		img_put_pixel(img, img->width - 1, y, color);
		y++;
	}
}
