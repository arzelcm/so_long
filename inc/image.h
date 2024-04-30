/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:45:07 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/30 15:11:10 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

typedef struct s_image
{
	int		x_size;
	int		y_size;
	void	*img;
}	t_image;

t_image *init_image(t_image *image, char *img_path, void *mlx);

#endif