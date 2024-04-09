/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:51:43 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/09 19:43:20 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAFE_UTILS_H
# define SAFE_UTILS_H

#include "context.h"

int		safe_open(const char *path, int mode, t_context *context);

int		safe_close(int *fd, t_context *context);

void	*safe_malloc(size_t size, t_context *context);

#endif