/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 12:57:05 by arcanava          #+#    #+#             */
/*   Updated: 2024/05/06 17:06:23 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "libft.h"
#include "loader.h"
#include "utils.h"

void	propagate_floodfill(t_map *map, t_pos_stack **stack, t_position *pos,
			t_checking_status *check_status)
{
	if (map->spaces[pos->y][pos->x] == COLLECTIBLE)
		check_status->elems.collectibles++;
	else if (map->spaces[pos->y][pos->x] == EXIT)
	{
		map->spaces[pos->y][pos->x] = 'A';
		check_status->elems.exit++;
		return ;
	}
	map->spaces[pos->y][pos->x] = 'A';
	if (map->spaces[pos->y][pos->x + 1] != 'A'
			&& map->spaces[pos->y][pos->x + 1]
				!= WALL)
		push_pos(stack, pos->x + 1, pos->y);
	if (map->spaces[pos->y][pos->x - 1] != 'A'
			&& map->spaces[pos->y][pos->x - 1]
				!= WALL)
		push_pos(stack, pos->x - 1, pos->y);
	if (map->spaces[pos->y + 1][pos->x] != 'A'
			&& map->spaces[pos->y + 1][pos->x]
				!= WALL)
		push_pos(stack, pos->x, pos->y + 1);
	if (map->spaces[pos->y - 1][pos->x] != 'A'
			&& map->spaces[pos->y - 1][pos->x]
				!= WALL)
		push_pos(stack, pos->x, pos->y - 1);
}

void	find_accessible_elems(t_checking_status *state)
{
	t_pos_stack	*stack;
	t_pos_stack	*aux_stack;

	stack = new_pos(state->map.player.pos.x, state->map.player.pos.y);
	while (stack)
	{
		aux_stack = stack;
		stack = stack->next;
		if (state->map.spaces[aux_stack->pos.y][aux_stack->pos.x] != 'A'
			&& state->map.spaces[aux_stack->pos.y][aux_stack->pos.x] != WALL)
		{
			pthread_mutex_lock(&state->iteration_mutex);
			state->elems.iterations++;
			pthread_mutex_unlock(&state->iteration_mutex);
			propagate_floodfill(&state->map, &stack, &aux_stack->pos, state);
		}
		free(aux_stack);
	}
	pthread_mutex_lock(&state->checked_mutex);
	state->map.checked = 1;
	pthread_mutex_unlock(&state->checked_mutex);
}

int	has_valid_path_map(t_map *map)
{
	t_checking_status	check_status;
	pthread_t			thread_id;

	copy_map(&check_status.map, map);
	check_status.elems.collectibles = 0;
	check_status.elems.exit = 0;
	check_status.elems.iterations = 0;
	pthread_mutex_init(&check_status.iteration_mutex, NULL);
	pthread_mutex_init(&check_status.checked_mutex, NULL);
	pthread_create(&thread_id, NULL, check_progress, &check_status);
	find_accessible_elems(&check_status);
	pthread_join(thread_id, NULL);
	update_loading("Checking map", 100);
	pthread_mutex_destroy(&check_status.iteration_mutex);
	pthread_mutex_destroy(&check_status.checked_mutex);
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
