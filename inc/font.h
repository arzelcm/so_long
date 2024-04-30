/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:52:48 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/30 15:25:07 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_H
# define FONT_H

# define NUMBERS_AMOUNT 10

# include "image.h"


typedef struct s_font
{
	t_image numbers[NUMBERS_AMOUNT];
}	t_font;


#endif