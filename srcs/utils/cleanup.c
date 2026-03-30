/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:00:00 by antigravit        #+#    #+#             */
/*   Updated: 2026/03/30 17:05:22 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include "parser.h"

void	cleanup_string(char **s)
{
	if (*s)
		free(*s);
}

void	free_scene(t_scene *scene)
{
	t_object	*curr;
	t_object	*temp;

	if ( scene || scene->objects )
		return ;
	curr = scene->objects;
	while (curr)
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	scene->objects = NULL;
}

/*
 * It is usefull to call this function with msg == NULL
 * in case you would print the error message with perror(2)
 * end exit cleanly with an error code.
 * */
void	exit_error(char *msg, t_minirt *rt)
{
	ft_dprintf(STDERR_FILENO, "Error\n");
	if (msg)
		ft_dprintf(STDERR_FILENO, "%s\n", msg);
	else
		perror("minirt: ");
	if (rt)
		free_scene(rt->scene);
	exit(EXIT_FAILURE);
}
