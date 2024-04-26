/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actuator.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:55:29 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/26 20:20:05 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTUATOR_H
# define ACTUATOR_H

# include "context.h"

int	on_key_down(int key, t_context *context);

int	on_key_up(int key, t_context *context);

int	background_loop(t_context *context);

#endif