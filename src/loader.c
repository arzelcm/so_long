/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:06:36 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/28 13:49:27 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	update_loading(char *message, int value)
{
	ft_printf("\033[1A\033[2K%s --> [%i%%]\n", message,
		ft_normalize(value, 0, 100));
}
