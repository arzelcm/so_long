/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:11:08 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/19 20:38:20 by arcanava         ###   ########.fr       */
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

	dst->spaces = safe_malloc(sizeof(char *) * src->max_y, NULL);
	i = -1;
	while (++i < src->max_y)
		push_string(ft_strdup(src->spaces[i]), &dst->spaces, i, NULL);
	dst->elems = NULL;
	dst->max_x = src->max_x;
	dst->max_y = src->max_y;
	dst->player.position.x = src->player.position.x;
	dst->player.position.y = src->player.position.y;
}

void	terminate_map(t_map *map)
{
	free_matrix(map->spaces, map->max_y);
	if (map->elems)
		free(map->elems);
}