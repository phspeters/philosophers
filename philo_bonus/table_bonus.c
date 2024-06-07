/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 21:07:05 by pehenri2          #+#    #+#             */
/*   Updated: 2024/06/07 18:22:14 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_table(t_table *table, char **argv)
{
	table->philo_count = string_to_size_t(argv[1]);
	table->time_to_die = string_to_size_t(argv[2]);
	table->time_to_eat = string_to_size_t(argv[3]);
	table->time_to_sleep = string_to_size_t(argv[4]);
	if (argv[5])
		table->meals_to_fullfil = string_to_size_t(argv[5]);
	else
		table->meals_to_fullfil = -1;
	table->dinner_over_sem = start_semaphore("/dinner_over_sem", 1);
	table->someone_died_sem = start_semaphore("/someone_died_sem", 0);
	table->philo_is_full_sem = start_semaphore("/philo_is_full_sem", 0);
	table->forks = start_semaphore("/forks", table->philo_count);
	table->philo = malloc(sizeof(t_philo));
	table->philo->id = 0;
	table->philo->meals_eaten = 0;
	table->philo->table = table;
	table->pids = malloc(sizeof(pid_t) * table->philo_count);
	table->reports = malloc(sizeof(pthread_t) * 2);
	table->is_dinner_over = false;
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

sem_t	*start_semaphore(char *name, size_t value)
{
	sem_t	*semaphore;

	sem_unlink(name);
	semaphore = sem_open(name, O_CREAT, S_IRUSR | S_IWUSR, value);
	sem_unlink(name);
	return (semaphore);
}

void	clean_the_table(t_table *table)
{
	sem_close(table->dinner_over_sem);
	sem_close(table->someone_died_sem);
	sem_close(table->philo_is_full_sem);
	sem_close(table->forks);
	free(table->philo);
	free(table->pids);
	free(table->reports);
}
