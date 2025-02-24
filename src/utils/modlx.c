/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   modlx.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/28 22:07:27 by simon         #+#    #+#                 */
/*   Updated: 2025/02/24 04:13:43 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	transpose_texture(
		mlx_texture_t *texture,
		uint8_t *pixelcopy)
{
	int			y;
	int			x;
	int			src_idx;
	int			dst_idx;

	y = 0;
	while (y < texture->height)
	{
		x = 0;
		while (x < texture->width)
		{
			src_idx = (y * texture->width + x) * texture->bytes_per_pixel;
			dst_idx = (x * texture->height + y) * texture->bytes_per_pixel;
			ft_memcpy(&texture->pixels[dst_idx], &pixelcopy[src_idx],
				texture->bytes_per_pixel);
			x++;
		}
		y++;
	}
}

// loads texture column-major (transposed over y = x)
xpm_t	*
	modlx_load_xpm42(
		const char *path)
{
	xpm_t		*xpm;
	uint8_t		*pixelcopy;
	size_t		pixeldata_size;

	xpm = mlx_load_xpm42(path);
	if (!xpm)
		return (NULL);
	pixeldata_size = xpm->texture.width * xpm->texture.height
		* sizeof(uint8_t) * xpm->texture.bytes_per_pixel;
	pixelcopy = malloc(pixeldata_size);
	if (!pixelcopy)
	{
		free(xpm->texture.pixels);
		free(xpm);
		return (NULL);
	}
	ft_memcpy(pixelcopy, xpm->texture.pixels, pixeldata_size);
	transpose_texture(&xpm->texture, pixelcopy);
	free(pixelcopy);
	return (xpm);
}

// writes new string in image created by mlx_put_string()
// fails if new string is longer than original
int
	modlx_put_string(
		mlx_image_t *strimage,
		const char* str)
{
	int32_t			imgoffset;
	const size_t	len = ft_strlen(str);
	size_t			i;

	if (len * FONT_WIDTH > strimage->width)
		return (RETURN_FAILURE);
	imgoffset = 0;
	i = 0;
	while(i < len)
	{
		mlx_draw_char(strimage, mlx_get_texoffset(str[i]), imgoffset);
		imgoffset += FONT_WIDTH;
		i++;
	}
	return (RETURN_SUCCESS);
}

void
	reset_image(
		mlx_image_t *image)
{
	uint8_t		*dst;
	uint8_t		*dst_limit;

	dst = image->pixels;
	dst_limit = dst + image->height * image->width * sizeof(uint32_t);
	while (dst < dst_limit)
	{
		dst[3] = 0x00;
		dst += sizeof(uint32_t);
	}
}
