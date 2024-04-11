/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:32:08 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/11 14:53:05 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H

# include "map.h"

typedef struct s_context
{
	t_map	map;
	void	*mlx;
	void	*window;
}	t_context;

#endif