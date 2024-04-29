/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:28:03 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/29 11:21:08 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POSITION_H
# define POSITION_H

# include "stdlib.h"

typedef struct s_position
{
	size_t	y;
	size_t	x;
}	t_position;

typedef struct s_lposition
{
	long	y;
	long	x;
}	t_lposition;

typedef struct s_iposition
{
	int	y;
	int	x;
}	t_iposition;

#endif