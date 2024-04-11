/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:11:08 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/11 17:32:59 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/libft.h"
#include "map.h"
#include "context.h"
#include "utils.h"
#include "safe_utils.h"

t_map *copy_map(t_map *map, t_context *context)
{
	size_t	i;

	map->spaces = safe_malloc(sizeof(char *) * context->map.max_y, context);
	i = -1;
	while (++i < context->map.max_y)
		push_string(context->map.spaces[i], &map->spaces, i, context);
	map->max_x = context->map.max_x;
	map->max_y = context->map.max_y;
	return (map);
}