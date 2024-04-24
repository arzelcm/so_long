/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_stack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:19:03 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/24 16:33:34 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "safe_utils.h"
#include "../lib/libft/libft.h"

t_pos_stack	*new_pos(size_t x, size_t y)
{
	t_pos_stack *pos;

	pos = safe_malloc(sizeof(t_pos_stack));
	pos->next = NULL;
	pos->pos.x = x;
	pos->pos.y = y;
	return (pos);
}

void	shift_pos(t_pos_stack **stack)
{
	*stack = (*stack)->next;
}

void	push_pos(t_pos_stack **stack, size_t x, size_t y)
{
	t_pos_stack *new;

	new = new_pos(x, y);
	new->next = *stack;
	*stack = new;
}

void	terminate_stack(t_pos_stack *stack)
{
	t_pos_stack *aux;

	while (stack)
	{
		ft_printf("Freeing %p\n", stack);
		aux = stack->next;
		free(stack);
		stack = aux;
	}
}