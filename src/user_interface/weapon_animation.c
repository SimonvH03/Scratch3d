/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   weapon_animation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/09 19:05:56 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/15 23:07:44 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	start_fire_animation(t_weapon *weapon)
{
	if (weapon->state != WS_IDLE || weapon->ammo == 0)
		return ;
	weapon->state = WS_FIRING;
	weapon->ammo--;
}

static void	start_reload_animation(t_weapon *weapon)
{
	if (weapon->state != WS_IDLE || weapon->ammo == weapon->mag_capacity)
		return ;
	weapon->state = WS_RELOADING;
	weapon->total_ammo += weapon->ammo;
	weapon->ammo = 0;
}

static void	update_fire_animation(t_weapon *weapon)
{
	if (weapon->fire[weapon->frame_index] != NULL)
	{
		weapon->scalable.texture = weapon->fire[weapon->frame_index];
	}
	else
	{
		weapon->state = WS_IDLE;
		weapon->frame_index = -1;
		weapon->scalable.texture = weapon->rest;
	}
}

static void	update_reload_animation(t_weapon *weapon)
{
	if (weapon->reload[weapon->frame_index] != NULL)
	{
		weapon->scalable.texture = weapon->reload[weapon->frame_index];
	}
	else
	{
		weapon->state = WS_IDLE;
		weapon->ammo = ft_min_int(weapon->mag_capacity, weapon->total_ammo);
		weapon->total_ammo -= weapon->ammo;
		weapon->frame_index = -1;
		weapon->scalable.texture = weapon->rest;
	}
}

void
	weapon_animation(
		mlx_t *mlx,
		t_weapon *weapon)
{
	if (mlx_is_key_down(mlx, MLX_KEY_G))
		start_fire_animation(weapon);
	if (mlx_is_key_down(mlx, MLX_KEY_R))
		start_reload_animation(weapon);
	if (weapon->state == WS_IDLE)
		return ;
	weapon->frame_time += mlx->delta_time;
	if (weapon->frame_time < weapon->frame_time_goal)
		return ;
	weapon->frame_time = 0;
	weapon->frame_index++;
	if (weapon->state == WS_FIRING)
		update_fire_animation(weapon);
	if (weapon->state == WS_RELOADING)
		update_reload_animation(weapon);
	image_iteration(weapon->scalable.image,
		sample_scalable, &weapon->scalable);
}
