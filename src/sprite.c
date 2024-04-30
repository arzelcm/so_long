/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:48:32 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/30 21:50:20 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprite.h"
#include "safe_utils.h"
#include "libft.h"

void	push_sprite(t_sprite **sprite, char *path, void *mlx)
{
	t_sprite	*last;
	t_sprite	*new;

	new = safe_malloc(sizeof(t_sprite));
	set_image(&new->image, path, mlx);
	if (!*sprite)
	{
		*sprite = new;
		(*sprite)->next = *sprite;
		return ;
	}
	last = *sprite;
	while (last->next != *sprite)
		last = last->next;
	last->next = new;
	new->next = *sprite;
}