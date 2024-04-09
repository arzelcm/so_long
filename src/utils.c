/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:28:06 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/09 20:02:48 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "context.h"
#include "safe_utils.h"
#include "../lib/libft/libft.h"
#include "so_long.h"
#include <stdio.h>

void	custom_error(char *message, t_context *context)
{
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
	(void) context;
	exit(EXIT_FAILURE);
}

void	error(t_context *context)
{
	perror(PROGRAM_NAME);
	// terminate_context(context);
	(void) context;
	exit(EXIT_FAILURE);
}
void	free_matrix(void **matrix)
{
	int	i;

	if (matrix)
	{
		i = 0;
		while (*(matrix + i))
			free(*(matrix + i++));
		free(matrix);
	}
}

void	dynamic_push(char *new, char ***matrix, int last_i, t_context *context)
{
	char **tmp;

	tmp = safe_malloc(sizeof(char *) * (last_i + 1), context);
	ft_memcpy(tmp, matrix, last_i);
	tmp[last_i + 1] = new;
	free(*matrix);
	*matrix = tmp;
}