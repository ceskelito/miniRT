/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legends_prints.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 14:15:14 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/16 15:46:53 by rceschel         ###   ########.fr       */
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

static const char	**g_op_set[] = {
	g_legend_resize,
	g_legend_translate,
	g_legend_rotate,
	NULL
};

static const char	*g_legend_camera[] = {
	"Camera Control",
	"C: Toggle Camera Control",
	NULL,
};

static const char	*g_legend_lights[] = {
	"Lights Control",
	"L: Toggle Lights Control",
	"P: Previous Light",
	"N: Next Light",
	NULL
};

static const char	*g_legend_other[] = {
	"Other commands",
	"Click on an object",
	"to focus on it",
	"",
	"Click on the background",
	"to remove objects focus",
	NULL
};

static const char	**g_right_set[] = {
	g_legend_camera,
	g_legend_lights,
	g_legend_other,
	NULL
};

static int	should_skip(t_scene *scene, const t_legends *set, int i)
{
	if ((i == ROTATE || i == RESIZE)
		&& scene->focused_right_legend != NO_LEGEND
		&& set->legends == g_op_set)
		return (1);
	return (0);
}

int	print_legends_set(t_mlx *mlx, t_scene *scene, const t_legends *set)
{
	int	printing_height;
	int	occupied_height;
	int	pos[2];
	int	i;

	printing_height = set->start_y;
	occupied_height = printing_height;
	i = 0;
	while (set->legends[i])
	{
		if (should_skip(scene, set, i))
		{
			i++;
			continue ;
		}
		occupied_height = printing_height;
		printing_height += print_background(mlx, set, i, printing_height);
		printing_height += 10;
		pos[0] = set->start_x + CHAR_WIDTH * 2;
		pos[1] = occupied_height + CHAR_HEIGHT * 2;
		print_text(mlx, set, i, pos);
		i++;
	}
	return (occupied_height);
}

int	print_operations_legend(t_minirt *rt)
{
	static t_legends	set;

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
	return (print_legends_set(&rt->mlx, &rt->scene, &set));
}

int	print_camera_legend(t_minirt *rt)
{
	static t_legends	set;

	set.start_x = WIN_WIDTH - (X + 25 + 200);
	set.start_y = Y;
	set.focused_legend = &rt->scene.focused_right_legend;
	set.colors_focused.background = WHITE;
	set.colors_focused.foreground = BLACK;
	set.colors_ignored.background = GREEN;
	set.colors_ignored.foreground = WHITE;
	set.legends = g_right_set;
	return (print_legends_set(&rt->mlx, &rt->scene, &set));
}
