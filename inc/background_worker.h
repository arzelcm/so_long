/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_worker.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 22:22:11 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/30 22:25:47 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BACKGROUND_WORKER_H
# define BACKGROUND_WORKER_H

# define KEY_ITERATION_DELAY 2000

# include "context.h"

int	background_loop(t_context *context);

#endif