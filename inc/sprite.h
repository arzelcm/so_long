/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:48:43 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/30 21:50:27 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

#include "image.h"

typedef struct s_sprite
{
	t_image 		image;
	struct s_sprite	*next;
} t_sprite;

void	push_sprite(t_sprite	**sprite, char *path, void *mlx);

#endif