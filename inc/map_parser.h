/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:05:25 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/28 14:03:15 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_PARSER_H
# define MAP_PARSER_H

# include "context.h"

void	use_map(t_map *map, t_context *context);

void	parse_map(t_map *map, t_context *context);

void	move_map_view(long x_increment, long y_increment,
			t_context *context);

#endif