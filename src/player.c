/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:35:59 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/24 18:52:35 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	init_player(t_player *player)
{
	player->pos.x = 0;
	player->pos.y = 0;
	player->collectibles = 0;
	player->movements = 0;
	player->moving = 0;
}
