/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_weapon.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 18:49:26 by svan-hoo      #+#    #+#                 */
/*   Updated: 2025/03/26 22:17:48 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int
	load_texture(
		mlx_texture_t **dest,
		const char *directory,
		const char *filename)
{
	char	*texture_path;
	char	*extended_filename;
	xpm_t	*temp_xpm;

	extended_filename = ft_strjoin(filename, ".xpm42");
	if (extended_filename == NULL)
		return (RETURN_ERROR);
	texture_path = ft_strjoin(directory, extended_filename);
	free(extended_filename);
	if (texture_path == NULL)
		return (RETURN_ERROR);
	temp_xpm = mlx_load_xpm42(texture_path);
	free(texture_path);
	if (temp_xpm == NULL)
		*dest = NULL;
	else
	{
		*dest = &temp_xpm->texture;
		add_to_clear_list(*dest);
	}
	return (RETURN_SUCCESS);
}

static int
	load_animation_textures(
		mlx_texture_t ***dest,
		const char *animation_id)
{
	char			*filename;
	char			*number;
	mlx_texture_t	*texture;
	unsigned int	i;
	int				return_value;

	i = 0;
	while (true)
	{
		number = ft_itoa(i++);
		if (number == NULL)
			return (RETURN_ERROR);
		filename = ft_strjoin(animation_id, number);
		free(number);
		return_value = load_texture(&texture, G1_TEXTURES_PATH, filename);
		free(filename);
		if (return_value != RETURN_SUCCESS)
			return (RETURN_ERROR);
		if (texture == NULL)
			return (RETURN_SUCCESS);
		*dest = (mlx_texture_t **)ft_arrcat((char **)*dest, (char *)texture);
		if (dest == NULL)
			return (RETURN_ERROR);
	}
}

static int
	load_weapon_textures(
		t_weapon *weapon)
{
	if (load_texture(&weapon->rest, G1_TEXTURES_PATH, "0")
		!= RETURN_SUCCESS)
		return (RETURN_ERROR);
	if (load_animation_textures(&weapon->fire, "f")
		!= RETURN_SUCCESS)
		return (RETURN_ERROR);
	if (load_animation_textures(&weapon->reload, "r")
		!= RETURN_SUCCESS)
		return (RETURN_ERROR);
	return (RETURN_SUCCESS);
}

int
	init_weapon(
		mlx_t *mlx,
		t_weapon *weapon)
{
	ft_bzero(weapon, sizeof(t_weapon));
	weapon->mag_capacity = G1_MAG_CAPACITY;
	weapon->ammo = weapon->mag_capacity;
	weapon->total_ammo = weapon->ammo * G1_SPARE_MAGS;
	weapon->damage = G1_DAMAGE;
	weapon->frame_index = -1;
	weapon->frame_time_goal = (1 / (float)G1_FRAME_RATE);
	if (load_weapon_textures(weapon) != RETURN_SUCCESS)
		return (RETURN_FAILURE);
	weapon->scalable.texture = weapon->rest;
	weapon->scalable.scale = mlx->width / (float)weapon->rest->width;
	weapon->scalable.image = mlx_new_image(mlx,
		mlx->width, weapon->rest->height * weapon->scalable.scale);
	if (weapon->scalable.image == NULL)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(mlx, weapon->scalable.image,
		0, mlx->height - weapon->scalable.image->height) < 0)
		return (EXIT_FAILURE);
	image_iter(weapon->scalable.image, sample_scalable, &weapon->scalable);
	return (RETURN_SUCCESS);
}
