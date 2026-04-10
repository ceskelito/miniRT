/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_legend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 14:15:14 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/10 16:10:15 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h" //exit_error() -- why is it defined in this header???
#include "mlx_imglib.h"

#define CHAR_HEIGHT	16	// pixels
#define CHAR_WIDTH	8	// pixels

#define MENU_ITEMS 3

enum { X = 10, Y = 20 };

enum { RESIZE = 0, TRANSFORM = 1, ROTATE = 2, NO_LEGEND = -1};

static const char *legend_resize[] = {
		"1 - Resize",
		"UP: increase size",
		"DN: decrease size",
		NULL
};

static const char *legend_transform[] = {
		"2 - Transform",
		NULL
};

static const char *legend_rotate[] = {
		"3 - Rotate",
		NULL
};

static const char **legends[] = {
	legend_resize,
	legend_transform,
	legend_rotate
};

static int count_elem(const char *legend[])
{
	int i;

	i = 0;
	while (legend[i])
		i++;
	return (i);
}

static void img_add_frame(t_img *img, int color)
{
    for (int x = 0; x < img->width; x++)
	{
        img_put_pixel(img, x, 0, color);
        img_put_pixel(img, x, img->height - 1, color);
    }

    for (int y = 0; y < img->height; y++)
	{
        img_put_pixel(img, 0, y, color);
        img_put_pixel(img, img->width - 1, y, color);
    }
}


int print_legend(t_minirt *rt)
{
	t_img	background;
	int		height;
	int		width;
	int		printing_height;


	/* DEBUG */
	rt->scene.expanded_legend = RESIZE;
	/* DEBUG */

	height = CHAR_HEIGHT * (MENU_ITEMS);
	if (rt->scene.expanded_legend != NO_LEGEND)
		height += CHAR_HEIGHT * count_elem(legends[rt->scene.expanded_legend]);

	width = CHAR_WIDTH * 20;

	if (img_create(rt->mlx.ptr, &background, width, height) == -1)
		exit_error("Failed in creating mlx's image", rt);
	if (img_set_background(&background, 0x000000))
		exit_error("Failed in filling mlx's image background", rt);
	img_add_frame(&background, 0xFFFFFF);

	mlx_put_image_to_window(rt->mlx.ptr, rt->mlx.win, background.img, X, Y);

	printing_height = Y + CHAR_HEIGHT;
	for (int i = 0; i < MENU_ITEMS; i++)
	{
		if (i != 0)
			printing_height += (CHAR_HEIGHT);
		mlx_string_put(rt->mlx.ptr, rt->mlx.win, X + 10, printing_height, 0xFFFFFF, (char *)legends[i][0]);
		if (rt->scene.expanded_legend == i)
		{
			for (int j = 1; legends[i][j]; j++)
			{
				printing_height += (CHAR_HEIGHT);
				mlx_string_put(rt->mlx.ptr, rt->mlx.win, X * 3 + 10, printing_height, 0xFFFFFF, (char *)(legends[i][j]));
			}
		}

	}
	return (0);
}
