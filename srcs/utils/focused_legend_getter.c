/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   focused_legend_getter.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 12:28:15 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/16 12:35:33 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define GET 0
#define SET 1

int *handle_focused_index(int mode, t_focused_legend_index index)
{
	static int focused_legend[2];

	if (mode == GET)
		return (focused_legend);
	if (mode == set)

}

int set_focused_index(int *index[]);
int get_focused_index(void);
