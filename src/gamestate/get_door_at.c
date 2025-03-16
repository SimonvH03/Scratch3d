/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_door_at.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:49:26 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/16 05:06:31 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_door	*
	get_door_at(
		t_doors *doors,
		unsigned int pos_y,
		unsigned int pos_x)
{
	unsigned int	index;
	t_door			*door;

	index = 0;
	while (index < doors->count)
	{
		door = &doors->list[index];
		if (door->pos_y == pos_y && door->pos_x == pos_x)
			return (door);
		index++;
	}
	return (NULL);
}
