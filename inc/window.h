/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:10:29 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/28 13:52:29 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include <stdlib.h>

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

#endif