/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_stack.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:27:19 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/24 18:50:48 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POSITION_STACK_H
# define POSITION_STACK_H

# include "position.h"

typedef struct s_pos_stack
{
	t_position			pos;
	struct s_pos_stack	*next;

}	t_pos_stack;

t_pos_stack	*new_pos(size_t x, size_t y);

void		push_pos(t_pos_stack **stack, size_t x, size_t y);

#endif