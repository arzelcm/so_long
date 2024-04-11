/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 19:54:07 by mel-kora          #+#    #+#             */
/*   Updated: 2022/05/30 19:59:22 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft.h"

void	ft_error(void)
{
	ft_putendl_fd("Error", 1);
	ft_putendl_fd("Something didn't go right :c", 1);
	exit(1);
}
