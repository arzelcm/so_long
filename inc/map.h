/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:23:16 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/20 16:03:22 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <stddef.h>

# define EMPTY '0'
# define WALL '1'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define PLAYER 'P'

typedef struct s_position
{
	size_t	y;
	size_t	x;
}	t_position;

typedef struct s_lposition
{
	long	y;
	long	x;
}	t_lposition;

typedef struct s_player
{
	t_position	pos;
	int			moving;
	size_t		collectibles;
	size_t		movements;
}	t_player;

typedef struct s_texture
{
	int		x_size;
	int		y_size;
	void	*img;
}	t_texture;

typedef struct s_map
{
	t_player	player;
	char		*path;
	char		*filename;
	char		*name;
	char		**spaces;
	char		*elems;
	t_texture	wall;
	t_texture	empty_space;
	t_lposition	position;
	size_t		max_y;
	size_t		max_x;
	size_t		walls_amount;
	size_t		collectible_amount;
	int			exit_amount;
	int			player_amount;
}	t_map;

typedef struct s_accessible_elems
{
	int			exit;
	size_t		collectibles;
	size_t		iterations;
}	t_elems;

typedef struct s_pos_stack
{
	t_position			pos;
	struct s_pos_stack	*next;

}	t_pos_stack;

void		terminate_map(t_map *map);

void		print_map(t_map *map);

t_pos_stack	*new_pos(size_t x, size_t y);

void		shift_pos(t_pos_stack **stack);

void		push_pos(t_pos_stack **stack, size_t x, size_t y);

void		terminate_stack(t_pos_stack *stack);

#endif