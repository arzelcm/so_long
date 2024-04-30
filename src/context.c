/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:18:52 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/30 22:26:56 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "image.h"
#include "mlx.h"

void	init_font(t_font *font, t_context *context)
{
	set_image(&font->numbers[0], "./assets/font/0.xpm", context->mlx);
	set_image(&font->numbers[1], "./assets/font/1.xpm", context->mlx);
	set_image(&font->numbers[2], "./assets/font/2.xpm", context->mlx);
	set_image(&font->numbers[3], "./assets/font/3.xpm", context->mlx);
	set_image(&font->numbers[4], "./assets/font/4.xpm", context->mlx);
	set_image(&font->numbers[5], "./assets/font/5.xpm", context->mlx);
	set_image(&font->numbers[6], "./assets/font/6.xpm", context->mlx);
	set_image(&font->numbers[7], "./assets/font/7.xpm", context->mlx);
	set_image(&font->numbers[8], "./assets/font/8.xpm", context->mlx);
	set_image(&font->numbers[9], "./assets/font/9.xpm", context->mlx);
}

void	init_mlx(void **mlx)
{
	*mlx = mlx_init();
}

void	init_context(t_context *context)
{
	init_mlx(&context->mlx);
	init_window(&context->window);
	init_font(&context->font, context);
}
