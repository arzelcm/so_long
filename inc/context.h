/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:32:08 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/16 12:18:42 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H

# include "map.h"

typedef struct s_window
{
	void	*ref;
	int		height;
	int		width;
	double	x_fact;
	double	y_fact;
	char	*title;
}	t_window;
typedef struct s_context
{
	t_map		map;
	void		*mlx;
	t_window	window;
}	t_context;

#endif