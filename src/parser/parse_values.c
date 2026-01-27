/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceskelito <ceskelito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:30:00 by ceskelito         #+#    #+#             */
/*   Updated: 2026/01/27 17:30:00 by ceskelito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int parse_double(const char *str, double *value) {
	if (!str || !value)
		return (0);
	*value = ft_atof(str);
	return (1);
}

int parse_int(const char *str, int *value) {
	if (!str || !value)
		return (0);
	*value = ft_atoi(str);
	return (1);
}
