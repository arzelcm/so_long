/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:03:12 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/30 21:12:34 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"
#include "mlx.h"

t_image *set_image(t_image *image, char *img_path, void *mlx)
{
	image->x_size = 0;
	image->y_size = 0;
	image->ref = mlx_xpm_file_to_image(mlx, img_path,
			&image->x_size, &image->y_size);
	return (image);
}