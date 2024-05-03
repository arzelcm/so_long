/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:41:38 by arcanava          #+#    #+#             */
/*   Updated: 2024/05/03 13:45:41 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

#include "context.h"

void	set_camera_initial_pos(t_map *map, t_context *context);

void	move_camera(long x_increment, long y_increment, t_context *context);

#endif