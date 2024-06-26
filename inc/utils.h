/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:27:06 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/24 18:49:28 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

void	custom_error(char *message);

void	error(void);

void	free_matrix(char **matrix, size_t len);

void	push_string(char *new, char ***matrix, size_t i);

void	push_char(char new, char **str);

#endif