/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 21:10:41 by pehenri2          #+#    #+#             */
/*   Updated: 2024/06/05 21:27:03 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_dinner(t_table *table)
{
	if (table->meals_to_fullfil == 0)
		return ;
	else
		sit_philosophers(table);
}

void	sit_philosophers(t_table *table)
{
	size_t	i;

	i = 0;
	table->dinner_start_time = get_time_in_ms();
	table->philo->last_meal_time = table->dinner_start_time;
	if (table->philo_count == 1)
	{
		table->philo->id = i + 1;
		table->philo->philo_turn = start_semaphore("/philo_turn", 1);
		assign_waiter(table->philo);
		lone_diner(&table->philo);
	}
	else
	{
		while (i < table->philo_count)
		{
			table->pids[i] = fork();
			if (table->pids[i] == 0)
			{
				table->philo->id = i + 1;
				table->philo->philo_turn = start_semaphore("/philo_turn", 1);
				assign_waiter(table->philo);
				dinner_routine(&table->philo);
			}
			i++;
		}
	}
}

void	*lone_diner(void *data)
{
	t_philo	*philo;
	t_table	*table;
	bool	wait_for_the_inevitable_embrace_of_death;

	philo = (t_philo *)data;
	table = philo->table;
	table->dinner_start_time = get_time_in_ms();
	sem_wait(philo->table->forks);
	safe_print_status(philo, GRABBED_FIRST_FORK);
	wait_for_the_inevitable_embrace_of_death = true;
	while (wait_for_the_inevitable_embrace_of_death)
		;
	return (NULL);
}

void	*dinner_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (true)
	{
		eat(philo);
		rest(philo);
		think(philo);
	}
	return (NULL);
}

bool	is_dinner_over(void)
{
	bool	answer;

	answer = false;
	if (waitpid(-1, NULL, WNOHANG) == -1)
		answer = true;
	return (answer);
}
