/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:17:57 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/10 22:05:36 by arcanava         ###   ########.fr       */
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

void	push_elems(char *str, t_context *context)
{
	size_t 	i;
	char	elem;

	i = 0;
	while (str[i])
	{
		elem = str[i];
		if (elem != EMPTY && elem != WALL)
			push_char(str[i], &context->map->elems, context);
		i++;
	}
}

void	set_map(char *path, t_context *context)
{
	char			*line;
	int				fd;
	int				correct;

	correct = 1;
	fd = safe_open(path, O_RDONLY, context);
	line = get_next_line(fd, 0);
	context->map->max_y = ft_strlen(line);
	while (line && correct)
	{
		if (context->map->max_y != ft_strlen(line))
			correct = 0;
		else
		{
			push_string(line, &context->map->spaces, context->map->max_x, context);
			push_elems(line, context);
			line = get_next_line(fd, 0);
		}
		context->map->max_x++;
	}
	close(fd);
	if (!correct)
		custom_error("map is not correct!", context);
}

void	check_extension(char *path, t_context *context)
{
	char	*filename;

	filename = ft_filename(path);
	if (ft_strlen(filename) <= 4 || ft_strnrcmp(filename, ".ber", 4) != EQUAL_STRINGS)
	{
		write(STDERR_FILENO, filename, ft_strlen(filename));
		custom_error(": invalid file extension, only .ber is allowed!", context);
	}
}

void	init_map(t_map *map, char *path, t_context *context)
{
	map->path = path;
	map->spaces = NULL;
	map->elems = NULL;
	map->max_x = 0;
	map->max_y = 0;
	context->map = map;
}

void	print_map(t_context *context)
{
	size_t i;

	ft_printf("Opened map: %s\n", context->map->path);
	i = -1;
	while (++i < context->map->max_x)
		ft_printf("%s\n", context->map->spaces[i]);
	ft_printf("Elems: %s\n", context->map->elems);
}

void	handle_map(int argc, char **argv, t_map *map, t_context *context)
{
	check_extension(argv[1], context);
	init_map(map, argv[1], context);
	set_map(argv[1], context);
	check_map(argc, argv);
	print_map(context);
}