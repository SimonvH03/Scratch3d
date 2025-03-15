/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: simon <simon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/24 02:16:25 by simon         #+#    #+#                 */
/*   Updated: 2025/03/15 21:38:16 by simon         ########   odam.nl         */
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
	ray->has_door = false;
}

static int
	evaluate_position(
		t_ray *ray,
		t_grid *grid,
		int pos_y,
		int pos_x)
{
	const int	cell_identifier = grid->walls[pos_y][pos_x];
	int			facing_cell;

	if (cell_identifier == 0)
		return (true);
	if (ft_isdigit(cell_identifier))
		return (false);
	if (cell_identifier == 'd' || cell_identifier == 'D')
	{
		if (ray->hit_type == HORIZONTAL)
			facing_cell = grid->walls[pos_y][pos_x - ray->sign_x];
		else
			facing_cell = grid->walls[pos_y - ray->sign_y][pos_x];
		if (facing_cell == 'd' || facing_cell == 'D')
			return (true);
		ray->door_state = grid->doors[pos_y][pos_x];
		if (cell_identifier == 'd')
			ray->fraction = 1 - ray->fraction;
		ray->has_door = (ray->fraction < ray->door_state);
		if (ray->has_door)
			ray->fraction += 1 - ray->door_state;
		return (!ray->has_door);
	}
	return (false);
}

// assuming the camera is not inside a wall;
//	shift map position to the nearest (total_y <> total_x) grid line;
//	and check wall type (-1, 0 or positive int 1-N)
static void
	cast_ray(
		t_ray *ray,
		t_grid *grid)
{
	while (ray->pos_x && ray->pos_x < grid->x_max
		&& ray->pos_y && ray->pos_y < grid->y_max)
	{
		if (ray->total_x < ray->total_y)
		{
			ray->total_x += ray->step_x;
			ray->pos_x += ray->sign_x;
			ray->hit_type = HORIZONTAL;
			ray->fraction = ray->start_y + (ray->total_x - ray->step_x) * ray->dir_y;
		}
		else
		{
			ray->total_y += ray->step_y;
			ray->pos_y += ray->sign_y;
			ray->hit_type = VERTICAL;
			ray->fraction = ray->start_x + (ray->total_y - ray->step_y) * ray->dir_x;
		}
		ray->fraction -= (int)ray->fraction;
		if (evaluate_position(ray, grid, ray->pos_y, ray->pos_x) == false)
			break ;
	}
	if (ray->hit_type == HORIZONTAL)
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
