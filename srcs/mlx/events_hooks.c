/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:30:13 by rceschel          #+#    #+#             */
/*   Updated: 2026/04/09 17:41:36 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
// #include "objects.h"

/***** START OF MOUSE OBJECT SELECTION *****/

/*
 * How to handle events:
 *
 * 1. On left click, check if the coordinates intersect an object
 *		(maybe we have an appropriate function yet..?)
 *		USE THE INTERSECT: shot a ray like for rendering
 *
 * 2. In case of, higlith the object
 * 2.1 Display a legend of possible commands
 *
 * 3. Apply trasformation on the selected object
 * */

/* Functions from:
 * srcs/objects/objects_utils.c 
 *
 * I will create an header
 * */
t_object	*get_selected_object(t_minirt *rt, int x, int y);
int			resize_object(t_object *selected, int resize_value);

int handle_mouse_events(int button, int x, int y, t_minirt *rt)
{
	t_object	*selected;
	int			resize_value;

	if (button == MOUSE_LEFT)
		resize_value = RESIZE_ABS_VALUE;
	else if (button == MOUSE_RIGHT)
		resize_value = RESIZE_ABS_VALUE * -1;
	else
		return (0);
	selected = get_selected_object(rt, x, y);
	if (selected)
	{
		if (resize_object(selected, resize_value))
			render(rt);
	}
	return (0);
}

/*
 * Teoricamente la cosa migliore sarebbe solo ottenere l'oggetto selezionato,
 * poi mostrare una legenda,
 * e infine gestire i keypress per operare sull'oggetto (resize, move, ...).
 *
 * Questa è una soluzione rudimentale e temporanea che confonde le responsabilità
 * delle funzioni.
 *
 * Ricorda: handle_mouse_events deve solo fare routing verso altre funzioni,
 * adesso gestisce già troppa logica che non le compete.
 * */

/***** END OF MOUSE OBJECT SELECTION *****/
