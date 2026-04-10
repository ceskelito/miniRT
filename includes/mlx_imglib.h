/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_imglib.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:27:08 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/10 14:39:16 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_IMGLIB_H
# define MLX_IMGLIB_H

# include "mlx.h"

# define MLX_ERROR -1

typedef struct s_img
{
	void	*img;

	char	*filename;	// for xpm images
	char	*addr;
	int		*pixels;	// same as addr, but 4 bytes aligned

	int		bpp;		// bits per pixel
	int		line_len;
	int		endian;
  
	int		width;		// to set manually if not xpm
	int		height;		// to set manually if not xpm
}				t_img;

int	img_set_background(t_img *img, int color);
int	img_get_offset(t_img *img, int x, int y);
int	img_put_pixel(t_img *img, int x, int y, int color);
int	img_get_offset_4_byte(int line_length, int x, int y);
int img_put_pixel_4_byte(int *pixels, int line_length,
			int x, int y, int color);
int	img_create(void *mlx, t_img *img, int img_width,
			int img_height);

#endif
