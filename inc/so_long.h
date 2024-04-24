/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:06:55 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/24 18:48:53 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define PROGRAM_NAME "so_long"

# define ESC_KEYCODE 53

# define UP_KEYCODE 126
# define DOWN_KEYCODE 125
# define LEFT_KEYCODE 123
# define RIGHT_KEYCODE 124

# define H_KEYCODE 4
# define J_KEYCODE 38
# define K_KEYCODE 40
# define L_KEYCODE 37

# define W_KEYCODE 13
# define A_KEYCODE 0
# define S_KEYCODE 1
# define D_KEYCODE 2

# ifndef WINDOW_MAX_WIDTH
#  define WINDOW_MAX_WIDTH 1422
# endif
# ifndef WINDOW_MAX_HEIGHT
#  define WINDOW_MAX_HEIGHT 800
# endif
# define TEXTURE_SIZE 50
# define EMPTY_TEXTURE "./assets/textures/empty-space.xpm"
# define WALL_TEXTURE "./assets/textures/wall.xpm"

#endif