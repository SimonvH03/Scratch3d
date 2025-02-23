/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_elements.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 16:58:42 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/02/23 20:05:32 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	load_texture(
		mlx_texture_t **dest,
		const char *line)
{
	xpm_t	*tempx;

	while (*line == ' ')
		++line;
	if (ft_strnstr(line, ".png", -1) != NULL)
	{
		*dest = mlx_load_png(line);
		if (*dest == NULL)
			error_exit(mlx_errno, 0, "failed to load .png file from scene");
	}
	else if (ft_strnstr(line, ".xpm42", -1) != NULL)
	{
		tempx = modlx_load_xpm42(line);
		if (tempx == NULL)
			error_exit(mlx_errno, 0, "failed to load .xpm42 file from scene");
		*dest = &tempx->texture;
	}
	else
		error_exit(0, EINVAL, "Only .png or .xpm42 textures in scene svp");
}

static void
	load_colour(
		uint32_t *dest,
		const char *line)
{
	t_colour_construct	new;

	while (*line == ' ')
		++line;
	new.a = 0xFF;
	new.r = ft_atoi(line);
	line = ft_strchr(line, ',') + 1;
	new.g = ft_atoi(line);
	line = ft_strchr(line, ',') + 1;
	new.b = ft_atoi(line);
	*dest = (uint32_t)((new.r << 24) | (new.g << 16) | (new.b << 8) | new.a);
}

void
	read_elements(
		t_scene *scene,
		char **const *content)
{
	int	element_count;

	element_count = 0;
	while (**content && element_count++ < 6)
	{
		if (ft_strncmp(**content, "NO ", 3) == 0)
			load_texture(&scene->walls.north_texture, &((**content)[3]));
		else if (ft_strncmp(**content, "EA ", 3) == 0)
			load_texture(&scene->walls.east_texture, &((**content)[3]));
		else if (ft_strncmp(**content, "SO ", 3) == 0)
			load_texture(&scene->walls.south_texture, &((**content)[3]));
		else if (ft_strncmp(**content, "WE ", 3) == 0)
			load_texture(&scene->walls.west_texture, &((**content)[3]));
		else if (ft_strncmp(**content, "F ", 2) == 0)
			load_colour(&scene->floor_clr, &((**content)[2]));
		else if (ft_strncmp(**content, "C ", 2) == 0)
			load_colour(&scene->ceiling_clr, &((**content)[2]));
		else if ((**content)[0] != '\0')
			error_exit(0, EINVAL, "missing or invalid scene.cub elements");
		else
			element_count--;
		*content++;
	}
}
