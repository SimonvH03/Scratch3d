/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <simon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/24 02:16:25 by simon         #+#    #+#                 */
/*   Updated: 2025/03/18 03:55:42 by simon         ########   odam.nl         */
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
	if (ray->hit_type == ha_horizontal)
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
		t_doors *doors,
		int16_t	cell)
{
	float old_partial = ray->partial;
	float new_partial = ray->partial;
	float new_total_x = ray->total_x;
	float new_total_y = ray->total_y;

	if (ray->hit_type == ha_horizontal)
		old_partial = ray->start_y
			+ (ray->total_x - ray->step_x) * ray->dir_y;
	else
		old_partial = ray->start_x
			+ (ray->total_y - ray->step_y) * ray->dir_x;


	if (ray->hit_type == ha_horizontal)
		new_total_x += ray->step_x * 0.5;
	else
		new_total_y += ray->step_y * 0.5;

	if (ray->hit_type == ha_horizontal)
		new_partial = ray->start_y
			+ (new_total_x - ray->step_x) * ray->dir_y;
	else
		new_partial = ray->start_x
			+ (new_total_y - ray->step_y) * ray->dir_x;
	if ((int)new_partial != (int)old_partial)
	{
		ray->hits_door = false;
		return ;
	}
	else
	{
		new_partial -= (int)new_partial;
		ray->partial = new_partial;
		ray->door_position = doors->list[get_id(cell)].position;
		if (get_type(cell) == 'd')
			ray->partial = 1 - ray->partial;
		ray->hits_door = (ray->partial < ray->door_position);
		if (ray->hits_door)
		{
			ray->partial += 1 - ray->door_position;
			ray->total_x = new_total_x;
			ray->total_y = new_total_y;
		}
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
	int16_t				facing_cell;
	// int16_t				side_cell0;
	// int16_t				side_cell1;

	if (is_solid(cell) == false)
		return (false);
	calculate_partial(ray);
	if (ft_isdigit(get_type(cell)))
		return (true);
	if (is_transparent(get_type(cell)))
	{
		if (ray->hit_type == ha_horizontal)
			facing_cell = grid->tilemap[pos_y][pos_x - ray->sign_x];
		else
			facing_cell = grid->tilemap[pos_y - ray->sign_y][pos_x];
		if (is_transparent(get_type(facing_cell)))
			return (false);
	}
	if (is_door(get_type(cell)))
	{
		// if (ray->hit_type == ha_horizontal)
		// {
		// 	side_cell0 = grid->tilemap[pos_y - 1][pos_x];
		// 	side_cell1 = grid->tilemap[pos_y + 1][pos_x];
		// 	if (!is_solid(side_cell0) && !is_solid(side_cell1))
		// 		ray->hit_type = ha_vertical;
		// }
		// else
		// {
		// 	side_cell0 = grid->tilemap[pos_y][pos_x - 1];
		// 	side_cell1 = grid->tilemap[pos_y][pos_x + 1];
		// 	if (!is_solid(side_cell0) && !is_solid(side_cell1))
		// 		ray->hit_type = ha_horizontal;
		// }
		calculate_partial(ray);
		door_half_step(ray, &grid->doors, cell);
		return (ray->hits_door);
	}
	return (true);
}

// assuming the camera is not inside a wall;
//	shift map position to the nearest (total_y <> total_x) grid line;
//	and check wall type (-1, 0 or positive int 1-N)
static void
	cast_ray(
		t_ray *ray,
		t_grid *grid)
{
	while (true)
	{
		if (ray->total_x < ray->total_y)
		{
			ray->total_x += ray->step_x;
			ray->pos_x += ray->sign_x;
			ray->hit_type = ha_horizontal;
		}
		else
		{
			ray->total_y += ray->step_y;
			ray->pos_y += ray->sign_y;
			ray->hit_type = ha_vertical;
		}
		if (hit_position(ray, grid, ray->pos_y, ray->pos_x) == true)
			break ;
	}
	if (ray->hit_type == ha_horizontal)
		ray->distance = ray->total_x - ray->step_x;
	else
		ray->distance = ray->total_y - ray->step_y;
}

void
	raycast(
		t_scene *scene)
{
	t_ray		ray;
	uint32_t	x;

	reset_image(scene->walls.image);
	x = 0;
	while (x < scene->walls.image->width)
	{
		ray.camera_x = 2 * x / (float)scene->walls.image->width - 1;
		init_ray(&ray, &scene->player.camera);
		cast_ray(&ray, &scene->grid);
		draw_texture_column(&ray, &scene->walls, x);
		++x;
	}
}
