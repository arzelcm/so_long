/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:27:06 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/09 20:03:14 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <stdlib.h>
# include "context.h"

void	custom_error(char *message, t_context *context);

void	error(t_context *context);

void	free_matrix(void **matrix);

void	dynamic_push(char *new, char ***matrix, int i, t_context *context);

#endif