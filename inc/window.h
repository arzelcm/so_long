/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:10:29 by arcanava          #+#    #+#             */
/*   Updated: 2024/05/03 13:30:28 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# ifndef WINDOW_MAX_WIDTH
#  define WINDOW_MAX_WIDTH 1422
# endif
# ifndef WINDOW_MAX_HEIGHT
#  define WINDOW_MAX_HEIGHT 800
# endif

# include <stdlib.h>
# include "map.h"

typedef struct s_window
{
	void	*ref;
	int		height;
	int		width;
	double	x_fact;
	double	y_fact;
	char	*title;
	size_t	loop_iter;
}	t_window;

void	init_window(t_window *window);

int		on_destroy(void);

void	set_window(t_window *window, t_map *map, void *mlx);

#endif