/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   host.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:58:44 by pehenri2          #+#    #+#             */
/*   Updated: 2024/05/30 21:49:37 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_on_philosophers(t_table *table)
{
	size_t	pos;
	t_philo	*philos;

	philos = table->philos;
	pos = 0;
	wait_for_all_philos_to_sit(table);
	while (pos < table->philo_count)
	{
		if ((get_time_in_ms() > safe_get(&philos[pos].philo_mutex,
					&philos[pos].last_meal_time) + table->time_to_die))
		{
			safe_print_status(&philos[pos], DEAD);
			break ;
		}
		if (safe_get(&philos[pos].philo_mutex, &philos[pos].is_full))
			pos++;
		else
			return ;
	}
	if (pos == table->philo_count)
		safe_print_status(philos, EVERYONE_FULL);
	safe_set(&table->table_mutex, &table->dinner_is_over, true);
}

void	escort_philosophers(t_table *table)
{
	size_t	pos;
	t_philo	*philos;

	pos = 0;
	philos = table->philos;
	while (pos < table->philo_count)
	{
		pthread_join(philos[pos].thread_id, NULL);
		pos++;
	}
}

bool	is_dinner_over(t_table *table)
{
	if (safe_get(&table->table_mutex, &table->dinner_is_over))
		return (true);
	return (false);
}
