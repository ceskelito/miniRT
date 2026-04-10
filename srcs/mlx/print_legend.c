/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_legend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 14:15:14 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/10 15:16:45 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h" //exit_error() -- why is it defined in this header???
#include "mlx_imglib.h"

#define CHAR_HEIGHT	16	// pixels
#define CHAR_WIDTH	8	// pixels

#define MENU_ITEMS 3

enum { RESIZE = 0, TRANSFORM = 1, ROTATE = 2, NO_LEGEND = -1};

static const char *legend_resize[] = {
		"1 - Resize",
		"UP: increase size",
		"DN: decrease size"
};

static const char *legend_transform[] = {
		"2 - Transform"
};

static const char *legend_rotate[] = {
		"3 - Rotate"
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

int print_legend(t_minirt *rt)
{
	t_img	background;
	int		height;
	int		width;


	/* DEBUG */
	rt->scene.expanded_legend = RESIZE;
	/* DEBUG */

	height = CHAR_HEIGHT * 3;
	if (rt->scene.expanded_legend != NO_LEGEND)
		height += CHAR_HEIGHT * count_elem(legends[rt->scene.expanded_legend]);

	width = CHAR_WIDTH * 20;

	if (img_create(rt->mlx.ptr, &background, width, height) == -1)
		exit_error("Failed in creating mlx's image", rt);
	if (img_set_background(&background, 0x000000))
		exit_error("Failed in filling mlx's image background", rt);
	
	mlx_put_image_to_window(rt->mlx.ptr, rt->mlx.win, background.img, 10, 10);

	for (int i = 0; i < MENU_ITEMS; i++)
	{
		mlx_string_put(rt->mlx.ptr, rt->mlx.win, 10, 10 + (CHAR_HEIGHT * i), 0xFFFFFF, (char *)legends[i][0]);
		if (rt->scene.expanded_legend == i)
		{
			for (int j = 1; legends[i][j]; j++)
			{
				mlx_string_put(rt->mlx.ptr, rt->mlx.win, 50, 10 + (CHAR_HEIGHT * i) + (CHAR_HEIGHT * j), 0xFFFFFF, (char *)(legends[i][j]));
			}
		}

	}
	return (0);
}
