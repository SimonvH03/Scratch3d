/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   allocation_list.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:51:01 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/26 22:24:36 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_to_clear_list(mlx_texture_t *texture_ptr)
{
	ft_lstadd_front(&g_texture_allocations, ft_lstnew(texture_ptr));
}

void	empty_clear_list(void)
{
	ft_lstclear(&g_texture_allocations, (void (*)(void *))mlx_delete_texture);
}
