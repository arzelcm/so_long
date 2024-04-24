/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:51:43 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/24 18:48:41 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAFE_UTILS_H
# define SAFE_UTILS_H

# include "stdlib.h"

int		safe_open(const char *path, int mode);

int		safe_close(int *fd);

void	*safe_malloc(size_t size);

#endif