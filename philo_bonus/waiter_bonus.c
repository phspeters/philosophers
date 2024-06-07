/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:12:06 by pehenri2          #+#    #+#             */
/*   Updated: 2024/06/07 17:50:18 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// penser se crio um waiter dando wait num semaphore que indica o final do role
// e que chamaria funcao de limpeza e exit
void	assign_waiter(t_philo *philo)
{
	pthread_t	waiter;

	pthread_create(&waiter, NULL, check_on_philosopher, philo);
	pthread_detach(waiter);
}

void	*check_on_philosopher(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)data;
	table = philo->table;
	while (true)
	{
		if ((get_time_in_ms() > safe_get(philo->meal_time_sem,
					&philo->last_meal_time) + table->time_to_die))
		{
			safe_print_status(philo, DEAD);
			sem_post(table->someone_died_sem);
			break ;
		}
	}
	return (NULL);
}
