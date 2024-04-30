/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:32:08 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/30 15:22:15 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H

# include "map.h"
# include "window.h"
# include "font.h"

typedef struct s_context
{
	t_map		map;
	void		*mlx;
	t_window	window;
	t_font		font;
}	t_context;

void	init_context(t_context *context);

#endif