/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 21:10:41 by pehenri2          #+#    #+#             */
/*   Updated: 2024/05/30 22:01:43 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_dinner(t_table *table)
{
	if (table->meals_to_fullfil == 0)
		safe_set(&table->table_mutex, &table->dinner_is_over, true);
	else
		sit_philosophers(table);
}

void	sit_philosophers(t_table *table)
{
	size_t	pos;

	pos = 0;
	if (table->philo_count == 1)
		pthread_create(&table->philos[0].thread_id, NULL, lone_diner,
			&table->philos[0]);
	else
	{
		table->dinner_start_time = get_time_in_ms();
		while (pos < table->philo_count)
		{
			pthread_create(&table->philos[pos].thread_id, NULL, dinner_routine,
				&table->philos[pos]);
			pos++;
		}
	}
	safe_set(&table->table_mutex, &table->all_philos_ready, true);
}

void	*lone_diner(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)data;
	table = philo->table;
	table->dinner_start_time = get_time_in_ms();
	safe_set(&philo->philo_mutex, &philo->last_meal_time,
		table->dinner_start_time);
	pthread_mutex_lock(&philo->first_fork->fork_mutex);
	safe_print_status(philo, GRABBED_FIRST_FORK);
	pthread_mutex_unlock(&philo->first_fork->fork_mutex);
	while (!is_dinner_over(table))
		;
	return (NULL);
}

void	*dinner_routine(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)data;
	table = philo->table;
	wait_for_all_philos_to_sit(table);
	safe_set(&philo->philo_mutex, &philo->last_meal_time,
		table->dinner_start_time);
	while (!is_dinner_over(table))
	{
		eat(philo);
		rest(philo);
		think(philo);
	}
	return (NULL);
}

void	wait_for_all_philos_to_sit(t_table *table)
{
	while (!safe_get(&table->table_mutex, &table->all_philos_ready))
		;
}
