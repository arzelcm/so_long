/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:11:17 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/26 19:40:32 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "window.h"

void init_window(t_window *window)
{
	window->height = 0;
	window->width = 0;
	window->loop_iter = 0;
	window->x_fact = 0;
	window->y_fact = 0;
	window->ref = NULL;
	window->title = NULL;
}

int	on_destroy(void)
{
	ft_printf("\033[?25h");
	exit(EXIT_SUCCESS);
}
