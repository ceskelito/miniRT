/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legends_prints.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 14:15:14 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/15 10:51:53 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "legend.h"
#include "minirt.h"

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

int print_legens(t_mlx *mlx, const char **legends[], int start_x, int start_y, int b_color, int f_color)
{

}

int	print_operations_legend(t_minirt *rt)
{
	int b_color;
	int f_color;
	int old_y;
	int y;

	if (!rt->scene.selected_object)
		return (0);
	y = Y;
	// Maybe i can put this cycle in a stand alone function?
	for (int i = 0; g_legends[i]; i++)
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

// CAMERA AND LIGHTS

static const char *g_legend_camera[] = {
	"C: Control Camera",
	NULL,
};

static const char *g_legend_lights[] = {
	"L: Control Lights",
	"P: Previous Light",
	"N: Next Light",
	NULL
};

static const t_legends g_right_legends = {
	.start_x = WIN_WIDTH - (X + 25 + 200),
	.start_y = Y,

	.colors_focused.background = WHITE,
	.colors_focused.foreground = BLACK,

	.colors_ignored.background = GREEN,
	.colors_ignored.foreground = WHITE,

	.legends = {
		g_legend_camera,
		g_legend_lights,
		NULL
	}
};

int print_camera_legend(t_minirt *rt)
{
	int ret;
	int start_y;
	int start_x;
	int b_color;
	int f_color;

	start_x = WIN_WIDTH - (X + 25 + 200);
	start_y = Y;

	b_color = GREEN;
	f_color = WHITE;
	// if rt->scene.right_legend != NO_LEGEND
	// {
	//		b_color = WHITE;
	//		f_color = BALCK;
	// }
	ret = print_background(&rt->mlx, g_legend_camera, b_color, f_color, start_x, start_y);
	print_text(&rt->mlx, g_legend_camera, f_color, start_x + CHAR_WIDTH * 2, start_y + CHAR_HEIGHT * 2);
	ret += 10;
	start_y += ret;
	ret += print_background(&rt->mlx, g_legend_lights, b_color, f_color, start_x, start_y);
	print_text(&rt->mlx, g_legend_lights, f_color, start_x + CHAR_WIDTH * 2, start_y + CHAR_HEIGHT * 2);
	return (ret);
}
