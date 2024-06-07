/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 21:07:05 by pehenri2          #+#    #+#             */
/*   Updated: 2024/06/07 18:21:52 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_table(t_table *table, char **argv)
{
	size_t	pos;

	table->philo_count = string_to_size_t(argv[1]);
	table->time_to_die = string_to_size_t(argv[2]);
	table->time_to_eat = string_to_size_t(argv[3]);
	table->time_to_sleep = string_to_size_t(argv[4]);
	if (argv[5])
		table->meals_to_fullfil = string_to_size_t(argv[5]);
	else
		table->meals_to_fullfil = -1;
	table->dinner_is_over = false;
	table->forks = malloc(sizeof(t_fork) * table->philo_count);
	table->philos = malloc(sizeof(t_philo) * table->philo_count);
	pthread_mutex_init(&table->table_mutex, NULL);
	pos = 0;
	while (pos < table->philo_count)
	{
		table->forks[pos].id = pos + 1;
		pthread_mutex_init(&table->forks[pos].fork_mutex, NULL);
		pos++;
	}
}

size_t	string_to_size_t(const char *str)
{
	size_t	result;

	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}

void	welcome_philosophers(t_table *table)
{
	size_t	pos;

	pos = 0;
	while (pos < table->philo_count)
	{
		table->philos[pos].id = pos + 1;
		table->philos[pos].meals_eaten = 0;
		table->philos[pos].is_full = false;
		table->philos[pos].table = table;
		assign_forks(table, pos);
		pthread_mutex_init(&table->philos[pos].philo_mutex, NULL);
		pos++;
	}
}

/**
 * @brief Function to assign the fork order to the philosopher. This function
 * is important to avoid deadlocks by creating contention between the
 * philosophers.
 * Even philosophers will pick the left fork first and then the right fork.
 * Odd philosophers will pick the right fork first and then the left fork.
 * 
 * @param table Pointer to the table struct
 * @param philo_pos Position of the philosopher in the table 
 */
void	assign_forks(t_table *table, size_t philo_pos)
{
	if (philo_pos % 2 == 0)
	{
		table->philos[philo_pos].first_fork = &table->forks[philo_pos];
		table->philos[philo_pos].second_fork = &table->forks[(philo_pos + 1)
			% table->philo_count];
	}
	else
	{
		table->philos[philo_pos].first_fork = &table->forks[(philo_pos + 1)
			% table->philo_count];
		table->philos[philo_pos].second_fork = &table->forks[philo_pos];
	}
}

void	clean_the_table(t_table *table)
{
	size_t	pos;

	pos = 0;
	while (pos < table->philo_count)
	{
		pthread_mutex_destroy(&table->forks[pos].fork_mutex);
		pos++;
	}
	free(table->forks);
	free(table->philos);
	pthread_mutex_destroy(&table->table_mutex);
}
