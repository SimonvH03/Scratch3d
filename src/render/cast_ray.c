/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_ray.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <simon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/24 02:16:25 by simon         #+#    #+#                 */
/*   Updated: 2025/03/20 02:24:00 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	int			steps;
	uint16_t	next_cell;

	if (ray->hit_type == ha_horizontal)
	{
		new_partial = ray->partial + (ray->step_y * 0.5) * ray->dir_x;
		if (new_partial < 0 || new_partial > 1)
		{
			steps = ft_abs((int)new_partial) + (new_partial < 0);
			if (ray->pos_x + ray->sign_x * steps < 0 || ray->pos_x + ray->sign_x * steps >= grid->x_max)
				return ;
			next_cell = grid->tilemap[ray->pos_y][ray->pos_x + ray->sign_x * steps];
			if (!is_door(get_type(next_cell)))
				return ;
			cell = next_cell;
		}
	}
	else
	{
		new_partial = ray->partial + (ray->step_x * 0.5) * ray->dir_y;
		if (new_partial < 0 || new_partial > 1)
		{
			steps = ft_abs((int)new_partial) + (new_partial < 0);
			if (ray->pos_y + ray->sign_y * steps < 0 || ray->pos_y + ray->sign_y * steps >= grid->y_max)
				return ;
			next_cell = grid->tilemap[ray->pos_y + ray->sign_y * steps][ray->pos_x];
			if (!is_door(get_type(next_cell)))
				return ;
			cell = next_cell;
		}
	}
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
