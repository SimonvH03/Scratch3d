/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tilemap_cell.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:51:01 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/17 17:45:09 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int16_t
	set_cell(
		const bool solid,
		const int id,
		const char type)
{
	return ((solid << SOLID_SHIFT)
		| ((id & 0x7F) << ID_SHIFT)
		| (type & TYPE_MASK));
}

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

bool
	is_solid(const int16_t cell)
{
	return ((bool)(cell & SOLID_MASK));
}

char
	get_type(const int16_t cell)
{
	return ((char)(cell & TYPE_MASK));
}

int
	get_id(const int16_t cell)
{
	return ((int)((cell & ID_MASK) >> ID_SHIFT));
}

bool
	is_door(const char type)
{
	return ((bool)(type == 'd' || type == 'D'));
}

bool
	is_transparent(const char type)
{
	// return ((bool)(type == 'g' || type == 'G'));
	return (is_door(type));
}
