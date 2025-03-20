/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_ray_simple_doors.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <simon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/24 02:16:25 by simon         #+#    #+#                 */
/*   Updated: 2025/03/20 02:12:25 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	init_ray(
		t_ray *ray,
		t_camera *camera)
{
	ray->pos_x = (int)camera->pos_x;
	ray->pos_y = (int)camera->pos_y;
	ray->dir_x = camera->dir_x + camera->plane_x * 0.5 * ray->camera_x;
	ray->dir_y = camera->dir_y + camera->plane_y * 0.5 * ray->camera_x;
	ray->step_x = ft_abs_float(1 / ray->dir_x);
	if (ray->step_x == INFINITY)
		ray->step_x = (float)UINT32_MAX;
	ray->step_y = ft_abs_float(1 / ray->dir_y);
	if (ray->step_y == INFINITY)
		ray->step_y = (float)UINT32_MAX;
	ray->sign_x = ft_sign_float(ray->dir_x);
	ray->sign_y = ft_sign_float(ray->dir_y);
	if (ray->sign_x > 0)
		ray->total_x = ((ray->pos_x + 1 - camera->pos_x) * ray->step_x);
	else
		ray->total_x = (camera->pos_x - ray->pos_x) * ray->step_x;
	if (ray->sign_y > 0)
		ray->total_y = ((ray->pos_y + 1 - camera->pos_y) * ray->step_y);
	else
		ray->total_y = (camera->pos_y - ray->pos_y) * ray->step_y;
	ray->start_x = camera->pos_x;
	ray->start_y = camera->pos_y;
	ray->distance = 0;
	ray->hits_door = false;
}

static void
	calculate_partial(
		t_ray *ray)
{
	if (ray->hit_type == ha_vertical)
		ray->partial = ray->start_y
			+ (ray->total_x - ray->step_x) * ray->dir_y;
	else
		ray->partial = ray->start_x
			+ (ray->total_y - ray->step_y) * ray->dir_x;
	ray->partial -= (int)ray->partial;
}

static void
	door_half_step(
		t_ray *ray,
		t_grid *grid,
		int16_t	cell)
{
	float		new_partial;

	if (ray->hit_type == ha_horizontal)
		new_partial = ray->partial + (ray->step_y * 0.5) * ray->dir_x;
	else
		new_partial = ray->partial + (ray->step_x * 0.5) * ray->dir_y;
	if (new_partial < 0 || new_partial > 1)
		return ;
	ray->partial = (new_partial - (int)new_partial) + (new_partial < 0);
	ray->door_position = grid->doors.list[get_id(cell)].position;
	if (get_type(cell) == 'd')
		ray->partial = 1 - ray->partial;
	ray->hits_door = (ray->partial < ray->door_position);
	if (ray->hits_door)
	{
		ray->partial += 1 - ray->door_position;
		ray->total_y += ray->step_y * 0.5;
		ray->total_x += ray->step_x * 0.5;
	}
}

static bool
	hit_position(
		t_ray *ray,
		t_grid *grid,
		int pos_y,
		int pos_x)
{
	const int16_t	cell = grid->tilemap[pos_y][pos_x];
	int16_t			facing_cell;

	if (is_solid(cell) == false && !is_door(get_type(cell)))
		return (false);
	calculate_partial(ray);
	if (ft_isdigit(get_type(cell)))
		return (true);
	if (is_transparent(get_type(cell)))
	{
		if (ray->hit_type == ha_horizontal)
			facing_cell = grid->tilemap[pos_y - ray->sign_y][pos_x];
		else
			facing_cell = grid->tilemap[pos_y][pos_x - ray->sign_x];
		if (is_transparent(get_type(facing_cell)))
			return (false);
	}
	if (is_door(get_type(cell)))
	{
		calculate_partial(ray);
		door_half_step(ray, grid, cell);
		return (ray->hits_door);
	}
	return (true);
}

// assuming the camera is not inside a wall;
//	shift map position to the nearest (total_y <> total_x) grid line;
//	and check wall type (-1, 0 or positive int 1-N)
void
	cast_ray(
		t_ray *ray,
		t_grid *grid)
{
	while (true)
	{
		if (ray->total_y < ray->total_x)
		{
			ray->total_y += ray->step_y;
			ray->pos_y += ray->sign_y;
			ray->hit_type = ha_horizontal;
		}
		else
		{
			ray->total_x += ray->step_x;
			ray->pos_x += ray->sign_x;
			ray->hit_type = ha_vertical;
		}
		if (hit_position(ray, grid, ray->pos_y, ray->pos_x) == true)
			break ;
	}
	if (ray->hit_type == ha_horizontal)
		ray->distance = ray->total_y - ray->step_y;
	else
		ray->distance = ray->total_x - ray->step_x;
}
