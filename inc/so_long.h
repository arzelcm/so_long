/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:06:55 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/09 18:34:47 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define PROGRAM_NAME "so_long"

# include "../lib/libft/libft.h"
# include "../lib/mlx/mlx.h"

# include "map.h"
# include "context.h"


void	handle_map(int argc, char **argv, t_context *context);

#endif