/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:45:07 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/30 22:15:18 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

typedef struct s_image
{
	int		x_size;
	int		y_size;
	void	*ref;
}	t_image;

t_image	*set_image(t_image *image, char *img_path, void *mlx);

#endif