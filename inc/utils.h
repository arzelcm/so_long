/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:27:06 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/10 21:44:34 by arcanava         ###   ########.fr       */
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

void	push_string(char *new, char ***matrix, size_t i, t_context *context);

void	push_char(char new, char **str, t_context *context);

#endif