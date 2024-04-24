/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:32:36 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/24 18:48:09 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "position.h"
# include "texture.h"

typedef struct s_player
{
	t_position	pos;
	int			moving;
	size_t		collectibles;
	size_t		movements;
	t_texture	texture;
}	t_player;

void	init_player(t_player *player);

#endif