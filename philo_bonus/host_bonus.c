/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   host_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:58:44 by pehenri2          #+#    #+#             */
/*   Updated: 2024/06/11 16:25:50 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	manage_waiters_report(t_table *table)
{
	pthread_t	*death_report;
	pthread_t	*fullness_report;

	death_report = table->reports;
	fullness_report = table->reports + 1;
	pthread_create(death_report, NULL, share_death_report, table);
	pthread_create(fullness_report, NULL, share_fullness_report, table);
}

void	*share_death_report(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	sem_wait(table->someone_died_sem);
	if (!is_dinner_over(table))
		end_dinner(table, DEAD);
	return (NULL);
}

void	*share_fullness_report(void *data)
{
	t_table	*table;
	size_t	full_philos;

	table = (t_table *)data;
	full_philos = 0;
	while (true)
	{
		sem_wait(table->philo_is_full_sem);
		full_philos++;
		if (full_philos == table->philo_count)
			break ;
	}
	if (!is_dinner_over(table))
		end_dinner(table, PHILO_FULL);
	return (NULL);
}

void	escort_philosophers(t_table *table)
{
	size_t	pos;

	pos = 0;
	while (pos < table->philo_count)
	{
		kill(table->pids[pos], SIGKILL);
		pos++;
	}
}

void	wait_for_dinner_to_end(t_table *table)
{
	pthread_join(table->reports[0], NULL);
	pthread_join(table->reports[1], NULL);
	while (waitpid(-1, NULL, 0) != -1)
		;
}
