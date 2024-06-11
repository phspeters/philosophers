/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 21:10:41 by pehenri2          #+#    #+#             */
/*   Updated: 2024/06/11 16:27:58 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start_dinner(t_table *table)
{
	if (table->meals_to_fullfil == 0)
		return ;
	else
		sit_philosophers(table);
}

void	sit_philosophers(t_table *table)
{
	size_t	philo_counter;

	philo_counter = 0;
	table->dinner_start_time = get_time_in_ms();
	table->philo->last_meal_time = table->dinner_start_time;
	if (table->philo_count == 1)
	{
		table->pids[philo_counter] = fork();
		if (table->pids[philo_counter] == 0)
			lone_diner(table->philo, philo_counter);
	}
	else
	{
		while (philo_counter < table->philo_count)
		{
			table->pids[philo_counter] = fork();
			if (table->pids[philo_counter] == 0)
				dinner_routine(table->philo, philo_counter);
			philo_counter++;
		}
	}
}

void	lone_diner(t_philo	*philo, size_t counter)
{
	t_table	*table;
	bool	wait_for_the_inevitable_embrace_of_death;

	table = philo->table;
	philo->id = counter + 1;
	philo->meal_time_sem = start_semaphore("/meal_time_sem", 1);
	assign_waiter(philo);
	table->dinner_start_time = get_time_in_ms();
	sem_wait(table->forks);
	safe_print_status(philo, GRABBED_FIRST_FORK);
	wait_for_the_inevitable_embrace_of_death = true;
	while (wait_for_the_inevitable_embrace_of_death)
		;
}

void	dinner_routine(t_philo	*philo, size_t counter)
{
	philo->id = counter + 1;
	philo->meal_time_sem = start_semaphore("/meal_time_sem", 1);
	assign_waiter(philo);
	while (true)
	{
		eat(philo);
		rest(philo);
		think(philo);
	}
}

void	end_dinner(t_table *table, t_status	status)
{
	size_t	counter;

	safe_set(table->dinner_over_sem, &table->is_dinner_over, true);
	escort_philosophers(table);
	if (status == PHILO_FULL)
	{
		sem_post(table->someone_died_sem);
		if (DEBUG_MODE == true)
			printf(MAG "All philosophers are full" RST "\n");
	}
	if (status == DEAD)
	{
		counter = 0;
		while (counter < table->philo_count)
		{
			sem_post(table->philo_is_full_sem);
			counter++;
		}
	}
}
