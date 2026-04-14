/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:32:03 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/14 16:48:01 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int object_rotate(int type, double *axe, int rotate_value)
{
	if (type == CYLINDER)
	{
		*axe += rotate_value;
		return (0);
	}

	return (1);
}

int object_translate(double *axe, int translate_value)
{
	*axe += translate_value;
	return (0);
}

int object_resize(t_object *selected, int resize_value)
{
	if (selected->type == SPHERE)
		selected->data.sp.diameter += resize_value;
	else if (selected->type == CYLINDER)
	{
		selected->data.cy.diameter += resize_value;
		selected->data.cy.height += resize_value;
	}
	else if (selected->type == TORUS)
	{
		selected->data.to.sml_r += ( (float) resize_value / 2 );
		selected->data.to.sml_r2 += pow(selected->data.to.sml_r, 2);
		selected->data.to.big_r += resize_value;
		selected->data.to.big_r2 += pow(selected->data.to.big_r, 2);
	}
	else
		return (0);
	return (1);
}

int resize_object(t_object *selected, int resize_value)
{
	// Need to change the calls of the function
	return object_resize(selected, resize_value);
}
