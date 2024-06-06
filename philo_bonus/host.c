/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   host.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:58:44 by pehenri2          #+#    #+#             */
/*   Updated: 2024/06/05 21:23:59 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	manage_waiters(t_table *table)
{
	pthread_t	death_report;
	pthread_t	fullness_report;

	pthread_create(&death_report, NULL, share_death_report, table);
	pthread_detach(death_report);
	pthread_create(&fullness_report, NULL, share_fullness_report, table);
	pthread_detach(fullness_report);
}

void	wait_for_dinner_to_end(void)
{
	while (waitpid(-1, NULL, 0) != -1)
		;
}

void	*share_death_report(void *data)
{
	t_table	*table;
	size_t	counter;

	table = (t_table *)data;
	counter = 0;
	sem_wait(table->someone_died);
	if (!is_dinner_over())
	{
		escort_philosophers(table);
		while (counter < table->philo_count)
		{
			sem_post(table->philo_is_full);
			counter++;
		}
	}
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
		sem_wait(table->philo_is_full);
		full_philos++;
		if (full_philos == table->philo_count)
			break ;
	}
	if (!is_dinner_over())
	{
		escort_philosophers(table);
		sem_post(table->someone_died);
	}
	return (NULL);
}

// mudar logica para dar post num semaforo até philo count para indicar
// o fim do role e cada philo dar free e exit para evitar leaks?
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
