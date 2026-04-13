/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legend.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:19:24 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/13 12:26:22 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEGEND_H
# define LEGEND_H

# define CHAR_HEIGHT	16	// pixels
# define CHAR_WIDTH	8	// pixels

# define MENU_ITEMS 3

enum { X = 10, Y = 20 };

enum { RESIZE = 0, TRANSFORM = 1, ROTATE = 2, NO_LEGEND = -1};

typedef struct s_minirt t_minirt;

int	print_legend(t_minirt *rt);

#endif
