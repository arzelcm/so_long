/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_stack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:19:03 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/18 18:51:41 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "safe_utils.h"
#include "../lib/libft/libft.h"

t_pos_stack	*new_pos(size_t x, size_t y)
{
	t_pos_stack *pos;

	pos = safe_malloc(sizeof(t_pos_stack), NULL);
	pos->next = NULL;
	pos->pos.x = x;
	pos->pos.y = y;
	return (pos);
}

void	shift_pos(t_pos_stack **stack)
{
	t_pos_stack	*aux;

	aux = (*stack)->next;
	free(*stack);
	*stack = aux;
}

void	push_pos(t_pos_stack *stack, size_t x, size_t y)
{
	while (stack->next)
		stack = stack->next;
	stack->next = new_pos(x, y);
}