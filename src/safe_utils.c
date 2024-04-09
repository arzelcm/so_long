/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:21:21 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/09 20:07:31 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../lib/libft/libft.h"
#include "safe_utils.h"
#include <stddef.h>
#include <fcntl.h>


int	safe_open(const char *path, int mode, t_context *context)
{
	int	res;

	res = open(path, mode);
	if (res == -1)
	{
		write(2, path, ft_strlen(path));
		custom_error(": No such file or directory", context);
		error(context);
	}
	return (res);
}

int	safe_close(int *fd, t_context *context)
{
	int	res;

	if (*fd == -1)
		return (-1);
	res = close(*fd);
	if (res == -1)
		error(context);
	*fd = -1;
	return (res);
}

void	*safe_malloc(size_t size, t_context *context)
{
	void	*res;

	res = malloc(size);
	if (!res)
		error(context);
	return (res);
}
