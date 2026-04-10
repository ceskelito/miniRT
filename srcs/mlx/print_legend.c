/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_legend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 14:15:14 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/10 16:34:04 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "legend.h"
#include "minirt.h"
#include "mlx_imglib.h"
#include "parser.h" //exit_error() -- why is it defined in this header???

static const char	*g_legend_resize[] = {
	"1 - Resize",
	"UP: increase size",
	"DN: decrease size",
	NULL
};

static const char	*g_legend_transform[] = {
	"2 - Transform",
	NULL
};

static const char	*g_legend_rotate[] = {
	"3 - Rotate",
	NULL
};

static const char	**g_legends[] = {
	g_legend_resize,
	g_legend_transform,
	g_legend_rotate
};

static int	count_elem(const char *g_legend[])
{
	int	i;

	i = 0;
	while (g_legend[i])
		i++;
	return (i);
}

static void	img_add_frame(t_img *img, int color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < img->width)
	{
		img_put_pixel(img, x, 0, color);
		img_put_pixel(img, x, img->height - 1, color);
		x++;
	}
	while (y < img->width)
	{
		img_put_pixel(img, 0, y, color);
		img_put_pixel(img, img->width - 1, y, color);
		y++;
	}
}

static void	print_background(t_minirt *rt)
{
	t_img	background;
	int		height;
	int		width;

	height = CHAR_HEIGHT * (MENU_ITEMS);
	if (rt->scene.expanded_legend != NO_LEGEND)
		height += CHAR_HEIGHT
			* count_elem(g_legends[rt->scene.expanded_legend]);
	width = CHAR_WIDTH * 20;
	if (img_create(rt->mlx.ptr, &background, width, height) == -1)
		exit_error("Failed in creating mlx's image", rt);
	if (img_set_background(&background, 0x000000))
		exit_error("Failed in filling mlx's image background", rt);
	img_add_frame(&background, 0xFFFFFF);
	mlx_put_image_to_window(rt->mlx.ptr, rt->mlx.win, background.img, X, Y);
	mlx_destroy_image(rt->mlx.ptr, background.addr);
}

static void	print_text(t_minirt *rt)
{
	int	printing_height;

	printing_height = Y + CHAR_HEIGHT;
	for (int i = 0; i < MENU_ITEMS; i++)
	{
		if (i != 0)
			printing_height += (CHAR_HEIGHT);
		mlx_string_put(rt->mlx.ptr, rt->mlx.win, X + 10, printing_height,
			0xFFFFFF, (char *)g_legends[i][0]);
		if (rt->scene.expanded_legend == i)
		{
			for (int j = 1; g_legends[i][j]; j++)
			{
				printing_height += (CHAR_HEIGHT);
				mlx_string_put(rt->mlx.ptr, rt->mlx.win, X * 3 + 10,
					printing_height, 0xFFFFFF, (char *)(g_legends[i][j]));
			}
		}
	}
}

int	print_legend(t_minirt *rt)
{
	/* DEBUG */
	rt->scene.expanded_legend = RESIZE;
	/* DEBUG */
	print_background(rt);
	print_text(rt);
	return (0);
}
