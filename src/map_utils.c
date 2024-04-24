/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:11:08 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/24 16:31:36 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/libft.h"
#include "map.h"
#include "context.h"
#include "utils.h"
#include "safe_utils.h"

void	copy_map(t_map *dst, t_map *src)
{
	size_t	i;

	dst->spaces = safe_malloc(sizeof(char *) * src->max_y);
	i = -1;
	while (++i < src->max_y)
		push_string(ft_strdup(src->spaces[i]), &dst->spaces, i);
	dst->elems = NULL;
	dst->max_x = src->max_x;
	dst->max_y = src->max_y;
	dst->player.pos.x = src->player.pos.x;
	dst->player.pos.y = src->player.pos.y;
}

void	terminate_map(t_map *map)
{
	free_matrix(map->spaces, map->max_y);
	if (map->elems)
		free(map->elems);
}