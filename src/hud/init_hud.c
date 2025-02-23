/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_hud.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <simon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/22 19:48:30 by simon         #+#    #+#                 */
/*   Updated: 2025/02/23 00:06:00 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

short
	hud_init(
		mlx_t *mlx,
		t_window *window,
		char *argv_scene)
{
	if (minimap_init() != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	if (map_init() != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
