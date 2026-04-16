/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_legend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 14:15:14 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/14 18:00:23 by rceschel         ###   ########.fr       */
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

static const char	*g_legend_translate[] = {
	"2 - Translate",
	"UP/DN: Move on Y axe",
	"LF/RT: Move on X axe",
	"Z/X  : Move on Z axe",
	NULL
};

static const char	*g_legend_rotate[] = {
	"3 - Rotate",
	"UP/DN: Rotate on X axe",
	"LF/RT: Rotate on Y axe",
	"A/D  : Rotate on Z axe",
	NULL
};

static const char	**g_legends[] = {
	g_legend_resize,
	g_legend_translate,
	g_legend_rotate,
	NULL
};

static int	count_elem(const char *g_legend[])
{
	int	i;

	i = 0;
	while (g_legend[i])
		i++;
	return (i);
}

#define WHITE 0xFFFFFF
#define BLACK 0x000000

static int print_background(t_mlx *mlx, const char *legend[], int b_color, int f_color, int x, int y)
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

static void print_text(t_mlx *mlx, const char *legend[], int color, int x, int y)
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

int	print_legend(t_minirt *rt)
{
	int b_color;
	int f_color;
	int old_y;
	int y;

	if (!rt->scene.selected_object && !rt->scene.selected_light)
		return (0);
	y = Y;
	if (rt->scene.selected_light)
	{
		const char	*g_legend_light[] = {
			"Light selected",
			"UP/DN: Move on Y axe",
			"LF/RT: Move on X axe",
			"Z/X  : Move on Z axe",
			"L    : Deselect light",
			NULL
		};

		print_background(&rt->mlx, g_legend_light, WHITE, BLACK, X, y);
		print_text(&rt->mlx, g_legend_light, BLACK, X + CHAR_WIDTH * 2, y + CHAR_HEIGHT * 2);
		return (0);
	}
	for (int i = 0; i < MENU_ITEMS; i++)
	{
		b_color = BLACK;
		f_color = WHITE;
		if (i == rt->scene.expanded_legend)
		{
			b_color = WHITE;
			f_color = BLACK;
		}
		old_y = y;
		y += print_background(&rt->mlx, g_legends[i], b_color, f_color, X, y);
		y += 10;	
		print_text(&rt->mlx, g_legends[i], f_color, X + CHAR_WIDTH * 2, old_y + CHAR_HEIGHT * 2);
	}
	return (0);
}
