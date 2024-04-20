/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:06:36 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/20 16:17:34 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/libft.h"

void	update_loading(char *message, int value)
{
	ft_printf("%s... (%i / 100)\n\033[1F", message, value);
}