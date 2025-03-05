/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   weapon_animation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/09 19:05:56 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/05 17:19:36 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	start_fire_animation(t_weapon *weapon)
{
	if (weapon->is_firing || weapon->is_reloading
		|| weapon->ammo == 0)
		return ;
	weapon->is_firing = true;
	weapon->ammo--;
}

static void	start_reload_animation(t_weapon *weapon)
{
	if (weapon->is_firing || weapon->is_reloading
		|| weapon->ammo == weapon->mag_capacity)
		return ;
	weapon->is_reloading = true;
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
		weapon->is_firing = false;
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
		weapon->is_reloading = false;
		weapon->ammo = ft_max_int(weapon->mag_capacity, weapon->total_ammo);
		weapon->total_ammo -= weapon->ammo;
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
	if (weapon->is_firing || weapon->is_reloading)
	{
		weapon->frame_time += mlx->delta_time;
		if (weapon->frame_time < weapon->frame_time_goal)
			return ;
		weapon->frame_time = 0;
		weapon->frame_index++;//not using frame 0, may be removed from both arrays if resting frame is saved
		if (weapon->is_firing)
			update_fire_animation(weapon);
		if (weapon->is_reloading)
			update_reload_animation(weapon);
		image_iteration(weapon->scalable.image,
			sample_scalable, &weapon->scalable);
	}
}
