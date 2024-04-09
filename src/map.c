/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:17:57 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/09 20:08:06 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "map.h"
#include "context.h"
#include "../lib/libft/libft.h"
#include "safe_utils.h"
#include "utils.h"

void	check_map(int argc, char **argv)
{
	(void) argv;
	(void) argc;
}
void	set_map(char **argv, t_context *context)
{
	char			*line;
	int				fd;
	int				correct;
	unsigned long	line_length;
	int				i;

	i = 0;
	correct = 1;
	fd = safe_open(argv[1], O_RDONLY, context);
	line = get_next_line(fd);
	line_length = ft_strlen(line);
	while (line && correct)
	{
		line = get_next_line(fd);
		if (line_length != ft_strlen(line))
			correct = 0;
		else
			dynamic_push(line, &context->map->elems, i, context);
		i++;
	}
	if (!correct)
		custom_error("map is not correct!", context);
}

void	handle_map(int argc, char **argv, t_context *context)
{
	// TODO: Check extension
	set_map(argv, context);
	check_map(argc, argv);
}