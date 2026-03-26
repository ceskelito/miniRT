/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:00:00 by antigravit        #+#    #+#             */
/*   Updated: 2026/02/06 11:08:50 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include "parser.h"

void	free_scene(t_minirt *rt)
{
	t_object	*curr;
	t_object	*temp;

	if (!rt)
		return ;
	curr = rt->scene.objects;
	while (curr)
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	rt->scene.objects = NULL;
}

void	exit_error(char *msg, t_minirt *rt)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	if (rt)
		free_scene(rt);
	exit(1);
}
