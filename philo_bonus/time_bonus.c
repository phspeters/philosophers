/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 07:55:14 by pehenri2          #+#    #+#             */
/*   Updated: 2024/06/07 17:50:18 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	get_time_in_ms(void)
{
	struct timeval	time;
	size_t			time_in_ms;

	if (gettimeofday(&time, NULL) == -1)
		return (!printf("Error getting time\n"));
	time_in_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_in_ms);
}

size_t	timestamp(size_t start_time)
{
	return (get_time_in_ms() - start_time);
}
