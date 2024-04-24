/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:21:21 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/24 18:52:49 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include <fcntl.h>

int	safe_open(const char *path, int mode)
{
	int	res;

	res = open(path, mode);
	if (res == -1)
	{
		ft_printff(STDERR_FILENO, "Error\n%s: ", path);
		custom_error("No such file or directory");
	}
	return (res);
}

int	safe_close(int *fd)
{
	int	res;

	if (*fd == -1)
		return (-1);
	res = close(*fd);
	if (res == -1)
		error();
	*fd = -1;
	return (res);
}

void	*safe_malloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (!res)
		error();
	return (res);
}
