/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   image_iteration.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/28 22:07:27 by simon         #+#    #+#                 */
/*   Updated: 2025/02/25 02:26:46 by simon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/// @brief applies a function for each coordinate of an image
/// will not continue after function() returns value other than 0
/// @param image the image to iterate over
/// @param function the function to apply at each (x, y) of image
/// @param param parameter to pass to function()
/// @return 0 if succesful, or return value of function() if it fails
int
	image_iteration(
		mlx_image_t	*image,
		imgiter_func function,
		void *param)
{
	uint32_t	x;
	uint32_t	y;
	int			return_value;

	return_value = RETURN_FAILURE;
	y = 0;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			return_value = function(image, param, x, y);
			if (return_value != RETURN_SUCCESS)
				break ;
			x++;
		}
		y++;
	}
	return (return_value);
}