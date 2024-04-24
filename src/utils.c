/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:28:06 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/24 16:44:48 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "context.h"
#include "safe_utils.h"
#include "../lib/libft/libft.h"
#include "so_long.h"
#include <stdio.h>

void	custom_error(char *message)
{
	ft_printff(STDERR_FILENO, "%s\n", message);
	exit(EXIT_FAILURE);
}

void	error(void)
{
	perror(PROGRAM_NAME);
	exit(EXIT_FAILURE);
}
void	free_matrix(char **matrix, size_t len)
{
	size_t	i;

	if (matrix)
	{
		i = 0;
		while (i < len && *(matrix + i))
			free(*(matrix + i++));
		free(matrix);
	}
}

void	push_string(char *new, char ***matrix, size_t last_i)
{
	char	**tmp;
	size_t		i;

	tmp = safe_malloc(sizeof(char *) * (last_i + 1));
	i = 0;
	while (i < last_i && matrix && *matrix)
	{
		tmp[i] = (*matrix)[i];
		i++;
	}
	tmp[i] = new;
	free(*matrix);
	*matrix = tmp;
}

void	push_char(char new, char **str)
{
	char	*tmp;
	size_t	last_i;

	last_i = ft_strlen(*str);
	tmp = safe_malloc(sizeof(char) * (last_i + 2));
	ft_strlcpy(tmp, *str, last_i + 1);
	tmp[last_i ] = new;
	tmp[last_i + 1] = '\0';
	free(*str);
	*str = tmp;
}
