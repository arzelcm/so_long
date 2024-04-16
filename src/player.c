/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:35:59 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/16 15:36:58 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "map.h"

void	init_player(t_player *player)
{
	player->position.x = 0;
	player->position.y = 0;
	player->collectibles = 0;
}