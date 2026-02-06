/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:00:00 by antigravit        #+#    #+#             */
/*   Updated: 2026/02/06 15:58:37 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	main(int argc, char **argv)
{
	t_minirt	rt;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./miniRT <filename.rt>\n", 2);
		return (1);
	}
	rt.scene.objects = NULL;
	rt.mlx = NULL;
	rt.win = NULL;
	printf("Parsing scene: %s\n", argv[1]);
	parse_scene(argv[1], &rt);
	printf("Parsing complete. Verifying data:\n");
	print_scene(&rt);
	free_scene(&rt);
	return (0);
}
