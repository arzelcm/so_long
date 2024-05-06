/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:11:08 by arcanava          #+#    #+#             */
/*   Updated: 2024/05/06 14:08:05 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "context.h"
#include "utils.h"
#include "safe_utils.h"

void	copy_map(t_map *dst, t_map *src)
{
	size_t	i;

	dst->spaces = safe_malloc(sizeof(char *) * src->max_y);
	i = -1;
	while (++i < src->max_y)
		dst->spaces[i] = ft_strdup(src->spaces[i]);
	dst->max_x = src->max_x;
	dst->max_y = src->max_y;
	dst->walls_amount = src->walls_amount;
	dst->collectible_amount = src->collectible_amount;
	dst->player.pos.x = src->player.pos.x;
	dst->player.pos.y = src->player.pos.y;
	dst->checked = 0;
}

void	terminate_map(t_map *map)
{
	free_matrix(map->spaces, map->max_y);
}

void	set_map_size(t_map *map, int fd)
{
	struct stat	stat;

	fstat(fd, &stat);
	map->size = stat.st_size;
}
