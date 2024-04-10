/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:28:06 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/10 22:02:10 by arcanava         ###   ########.fr       */
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

void	push_string(char *new, char ***matrix, size_t last_i, t_context *context)
{
	char	**tmp;
	size_t		i;

	tmp = safe_malloc(sizeof(char *) * (last_i + 1), context);
	i = 0;
	while (i < last_i && *matrix)
	{
		tmp[i] = (*matrix)[i];
		i++;
	}
	tmp[i] = new;
	free(*matrix);
	*matrix = tmp;
}

void	push_char(char new, char **str, t_context *context)
{
	char	*tmp;
	size_t	last_i;

	last_i = ft_strlen(*str);
	tmp = safe_malloc(sizeof(char) * (last_i + 1), context);
	ft_strlcpy(tmp, *str, last_i + 1);
	tmp[last_i] = new;
	tmp[last_i + 1] = '\0';
	free(*str);
	*str = tmp;
}
