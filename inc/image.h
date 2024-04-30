/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:45:07 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/30 21:12:33 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

typedef struct s_image
{
	int		x_size;
	int		y_size;
	void	*ref;
}	t_image;

t_image *set_image(t_image *image, char *img_path, void *mlx);

#endif