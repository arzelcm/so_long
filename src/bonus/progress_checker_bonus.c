/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress_checker_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:10:49 by arcanava          #+#    #+#             */
/*   Updated: 2024/05/06 17:06:25 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "loader.h"
#include "libft.h"

void	*check_progress(void *param)
{
	size_t				iterations;
	t_checking_status	*check_status;
	size_t				i;
	size_t				curr_iteration;

	check_status = (t_checking_status *) param;
	i = 0;
	curr_iteration = 0;
	iterations = (check_status->map.max_x) * (check_status->map.max_x)
		- check_status->map.walls_amount - check_status->map.collectible_amount;
	while (42)
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
