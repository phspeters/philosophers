/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 21:07:05 by pehenri2          #+#    #+#             */
/*   Updated: 2024/06/06 15:41:38 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	table->someone_died = start_semaphore("/someone_died", 0);
	table->philo_is_full = start_semaphore("/philo_is_full", 0);
	table->print_turn = start_semaphore("/print_turn", 1);
	table->forks = start_semaphore("/forks", table->philo_count);
	table->philo = malloc(sizeof(t_philo));
	table->philo->id = 0;
	table->philo->meals_eaten = 0;
	table->philo->table = table;
	table->pids = malloc(sizeof(pid_t) * table->philo_count);
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
	sem_close(table->someone_died);
	sem_close(table->philo_is_full);
	sem_close(table->print_turn);
	sem_close(table->forks);
	free(table->philo);
	free(table->pids);
}
