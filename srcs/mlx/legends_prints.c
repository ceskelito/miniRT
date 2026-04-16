/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legends_prints.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 14:15:14 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/16 15:38:29 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "legend.h"
#include "minirt.h"

// Left Legends: Operations to perform.
static const char		*g_legend_resize[] = {
	"1 - Resize",
	"UP: increase size",
	"DN: decrease size",
	NULL
};

static const char		*g_legend_translate[] = {
	"2 - Translate",
	"UP/DN: Move on Y axe",
	"LF/RT: Move on X axe",
	"Z/X  : Move on Z axe",
	NULL
};

static const char		*g_legend_rotate[] = {
	"3 - Rotate",
	"UP/DN: Rotate on X axe",
	"LF/RT: Rotate on Y axe",
	"A/D  : Rotate on Z axe",
	NULL
};

static const char	**g_op_set[]  = {
	g_legend_resize,
	g_legend_translate,
	g_legend_rotate,
	NULL
};


// static const t_legends	g_operations_set = {
// 	.start_x = X,
// 	.start_y = Y,	
// 	.colors_focused.background = WHITE,
// 	.colors_focused.foreground = BLACK,
// 	.colors_ignored.background = BLACK,
// 	.colors_ignored.foreground = WHITE,
// 	.legends = {
// 	g_legend_resize,
// 	g_legend_translate,
// 	g_legend_rotate,
// 	NULL
// }
// };

// Right Legends: Camera and Lights selection; Other operations.

static const char		*g_legend_camera[] = {
	"Camera Control",
	"C: Control Camera",
	NULL,
};

static const char		*g_legend_lights[] = {
	"Lights Control",
	"L: Control Lights",
	"P: Previous Light",
	"N: Next Light",
	NULL
};

static const char		*g_legend_other[] = {
	"Other commands",
	"R: Render again",
	"X: Remove focus",
	"",
	"Click on an object",
	"to select it",
	NULL
};

static const char	**g_right_set[] = {
	g_legend_camera,
	g_legend_lights,
	g_legend_other,
	NULL
};

// static const t_legends	g_right_set = {
// 	.start_x = WIN_WIDTH - (X + 25 + 200),
// 	.start_y = Y,
// 	.colors_focused.background = WHITE,
// 	.colors_focused.foreground = BLACK,
// 	.colors_ignored.background = GREEN,
// 	.colors_ignored.foreground = WHITE,
// 	.legends = {
// 	g_legend_camera,
// 	g_legend_lights,
// 	g_legend_other,
// 	NULL
// }
// };

int	print_legends_set(t_mlx *mlx, t_scene *scene, const t_legends *set)
{
	int				printing_height;
	int				occupied_height;
	int				i;

	printing_height = set->start_y;
	i = 0;
	while (set->legends[i])
	{
		// Selected Lights or Camera: they cannot be resized
		if ( (i == ROTATE || i == RESIZE ) && scene->focused_right_legend != NO_LEGEND)
		{
			i++;
			continue ;
		}
		occupied_height = printing_height;
		printing_height += print_background(mlx, set, i, printing_height);
		printing_height += 10;
		print_text(mlx, set, i, set->start_x + CHAR_WIDTH * 2,
			occupied_height + CHAR_HEIGHT * 2);
		i++;
	}
	return (occupied_height);
}

int	print_operations_legend(t_minirt *rt)
{
	static t_legends	set;
	int	ret;

	set.start_x = X;
	set.start_y = Y;
	set.focused_legend = &rt->scene.focused_op_legend;
	set.colors_focused.background = WHITE;
	set.colors_focused.foreground = BLACK;
	set.colors_ignored.background = BLACK;
	set.colors_ignored.foreground = WHITE;
	set.legends = g_op_set;
	if (!rt->scene.selected_object
		&& rt->scene.focused_right_legend == NO_LEGEND)
		return (0);
	ret = print_legends_set(&rt->mlx, &rt->scene, &set);
	return (ret);
}

int	print_camera_legend(t_minirt *rt)
{
	static t_legends	set;
	int	ret;

	set.start_x = WIN_WIDTH - (X + 25 + 200);
	set.start_y = Y;
	set.focused_legend = &rt->scene.focused_right_legend;
	set.colors_focused.background = WHITE;
	set.colors_focused.foreground = BLACK;
	set.colors_ignored.background = GREEN;
	set.colors_ignored.foreground = WHITE;
	set.legends = g_right_set;
	ret = print_legends_set(&rt->mlx, &rt->scene, &set);
	return (ret);
}
