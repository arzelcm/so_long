/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_stack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:19:03 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/24 18:54:34 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "position_stack.h"
#include "safe_utils.h"

t_pos_stack	*new_pos(size_t x, size_t y)
{
	t_pos_stack	*pos;

	pos = safe_malloc(sizeof(t_pos_stack));
	pos->next = NULL;
	pos->pos.x = x;
	pos->pos.y = y;
	return (pos);
}

void	push_pos(t_pos_stack **stack, size_t x, size_t y)
{
	t_pos_stack	*new;

	new = new_pos(x, y);
	new->next = *stack;
	*stack = new;
}
