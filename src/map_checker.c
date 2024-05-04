/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 12:57:05 by arcanava          #+#    #+#             */
/*   Updated: 2024/05/04 13:10:20 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "libft.h"
#include "loader.h"
#include "utils.h"

void	*check_progress(void *param)
{
	size_t				iterations;
	t_checking_status	*check_status;
	size_t				i;
	size_t				curr_iteration;

	check_status = (t_checking_status *) param;
	i = 0;
	iterations = (check_status->map.max_x) * (check_status->map.max_x)
		- check_status->map.walls_amount - check_status->map.collectible_amount;
	while (1)
	{
		if (i++ % 1000000 == 0)
		{
			pthread_mutex_lock(&check_status->checked_mutex);
			if (check_status->map.checked)
				return (NULL);
			pthread_mutex_unlock(&check_status->checked_mutex);
			pthread_mutex_lock(&check_status->iteration_mutex);
			curr_iteration = check_status->elems.iterations;
			pthread_mutex_unlock(&check_status->iteration_mutex);
			update_loading("Checking map", curr_iteration * 100 / iterations);
		}
	}
	return (NULL);
}

void	find_accessible_elems(t_checking_status *check_status)
{
	t_pos_stack	*stack;
	t_pos_stack	*actual_stack;
	t_map		*map;
	t_elems		*elems;
	pthread_t	thread_id;

	map = &check_status->map;
	elems = &check_status->elems;
	map->checked = 0;
	pthread_mutex_init(&check_status->iteration_mutex, NULL);
	pthread_mutex_init(&check_status->checked_mutex, NULL);
	pthread_create(&thread_id, NULL, check_progress, check_status);
	stack = new_pos(map->player.pos.x, map->player.pos.y);
	while (stack)
	{
		actual_stack = stack;
		stack = stack->next;
		if (map->spaces[actual_stack->pos.y][actual_stack->pos.x] == 'A'
			|| map->spaces[actual_stack->pos.y][actual_stack->pos.x] == WALL)
		{
			free(actual_stack);
			continue ;
		}
		else if (map->spaces[actual_stack->pos.y][actual_stack->pos.x] == EXIT)
		{
			elems->exit++;
			map->spaces[actual_stack->pos.y][actual_stack->pos.x] = 'A';
			free(actual_stack);
			continue ;
		}
		else if (map->spaces[actual_stack->pos.y][actual_stack->pos.x] == COLLECTIBLE)
			elems->collectibles++;
		map->spaces[actual_stack->pos.y][actual_stack->pos.x] = 'A';
		pthread_mutex_lock(&check_status->iteration_mutex);
		elems->iterations++;
		pthread_mutex_unlock(&check_status->iteration_mutex);
		if (map->spaces[actual_stack->pos.y][actual_stack->pos.x + 1] != 'A'
				&& map->spaces[actual_stack->pos.y][actual_stack->pos.x + 1] != WALL)
			push_pos(&stack, actual_stack->pos.x + 1, actual_stack->pos.y);
		if (map->spaces[actual_stack->pos.y][actual_stack->pos.x - 1] != 'A'
				&& map->spaces[actual_stack->pos.y][actual_stack->pos.x - 1] != WALL)
			push_pos(&stack, actual_stack->pos.x - 1, actual_stack->pos.y);
		if (map->spaces[actual_stack->pos.y + 1][actual_stack->pos.x] != 'A'
				&& map->spaces[actual_stack->pos.y + 1][actual_stack->pos.x] != WALL)
			push_pos(&stack, actual_stack->pos.x, actual_stack->pos.y + 1);
		if (map->spaces[actual_stack->pos.y - 1][actual_stack->pos.x] != 'A'
				&& map->spaces[actual_stack->pos.y - 1][actual_stack->pos.x] != WALL)
			push_pos(&stack, actual_stack->pos.x, actual_stack->pos.y - 1);
		free(actual_stack);
	}
	pthread_mutex_lock(&check_status->checked_mutex);
	map->checked = 1;
	pthread_mutex_unlock(&check_status->checked_mutex);
	pthread_join(thread_id, NULL);
	update_loading("Checking map", 100);
	pthread_mutex_destroy(&check_status->iteration_mutex);
	pthread_mutex_destroy(&check_status->checked_mutex);
}


int	has_valid_path_map(t_map *map)
{
	t_checking_status	check_status;

	copy_map(&check_status.map, map);
	check_status.elems.collectibles = 0;
	check_status.elems.exit = 0;
	check_status.elems.iterations = 0;
	find_accessible_elems(&check_status);
	terminate_map(&check_status.map);
	return (check_status.elems.exit == map->exit_amount
		&& check_status.elems.collectibles == map->collectible_amount);
}

int	is_closed_map(t_map *map)
{
	size_t	i;
	size_t	j;
	int		closed;

	closed = 1;
	i = 0;
	while (map && i < map->max_y && closed)
	{
		j = 0;
		while (j < map->max_x && closed)
		{
			if (i == 0 || i == map->max_y - 1 || j == 0 || j == map->max_x - 1)
				closed = map->spaces[i][j] == WALL;
			j++;
		}
		i++;
	}
	return (closed);
}

void	check_map(t_map *map)
{
	char	*message;

	if (map->player_amount != 1)
		message = "map must have one starting position for player";
	else if (map->exit_amount != 1)
		message = "map must have one exit";
	else if (map->collectible_amount < 1)
		message = "map must have at least one collectible";
	else if (!is_closed_map(map))
		message = "map must be sorrounded by walls";
	else if (!has_valid_path_map(map))
		message = "collectibles and exit must be acessible by player";
	else
		return ;
	ft_printff(STDERR_FILENO, "\033[1A\033[2KError\n%s: %s\n\033[?25h",
		map->path, message);
	exit(EXIT_FAILURE);
}

void	check_extension(t_map *map)
{
	if (ft_strlen(map->filename) <= 4
		|| ft_strnrcmp(map->filename, ".ber", 4) != EQUAL_STRINGS)
	{
		ft_printff(STDERR_FILENO, "\033[1A\033[2KError\n%s: ", map->filename);
		custom_error("invalid file extension, only .ber is allowed!");
	}
}