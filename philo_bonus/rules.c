/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:59:48 by pehenri2          #+#    #+#             */
/*   Updated: 2024/06/05 21:17:39 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	safe_get(sem_t *semaphore, size_t *value)
{
	size_t	get_value;

	sem_wait(semaphore);
	get_value = *value;
	sem_post(semaphore);
	return (get_value);
}

void	safe_set(sem_t *semaphore, size_t *value, size_t new_value)
{
	sem_wait(semaphore);
	*value = new_value;
	sem_post(semaphore);
}

void	safe_print_status(t_philo *philo, t_status status)
{
	t_table	*table;

	table = philo->table;
	sem_wait(table->print_turn);
	if (DEBUG_MODE == true)
		print_debug(philo, status);
	else
		print_status(philo, status);
	sem_post(table->print_turn);
}

void	print_debug(t_philo *philo, t_status status)
{
	t_table	*table;

	table = philo->table;
	if (status == DEAD)
		printf("%zu %zu died\n", timestamp(table->dinner_start_time),
			philo->id);
	else if (status == THINKING)
		printf("%zu %zu is thinking\n", timestamp(table->dinner_start_time),
			philo->id);
	else if (status == EATING)
		printf("%zu %zu is eating for the [%zu] time\n",
			timestamp(table->dinner_start_time), philo->id, philo->meals_eaten);
	else if (status == SLEEPING)
		printf("%zu %zu is sleeping\n", timestamp(table->dinner_start_time),
			philo->id);
	else if (status == GRABBED_FIRST_FORK)
		printf("%zu %zu has taken his first fork\n",
			timestamp(table->dinner_start_time), philo->id);
	else if (status == GRABBED_SECOND_FORK)
		printf("%zu %zu has taken his second fork\n",
			timestamp(table->dinner_start_time), philo->id);
	else if (status == EVERYONE_FULL)
		printf("All philosophers are full\n");
}

void	print_status(t_philo *philo, t_status status)
{
	t_table	*table;

	table = philo->table;
	if (status == DEAD)
		printf("%zu %zu died\n", timestamp(table->dinner_start_time),
			philo->id);
	else if (status == THINKING)
		printf("%zu %zu is thinking\n", timestamp(table->dinner_start_time),
			philo->id);
	else if (status == EATING)
		printf("%zu %zu is eating\n", timestamp(table->dinner_start_time),
			philo->id);
	else if (status == SLEEPING)
		printf("%zu %zu is sleeping\n", timestamp(table->dinner_start_time),
			philo->id);
	else if (status == GRABBED_FIRST_FORK || status == GRABBED_SECOND_FORK)
		printf("%zu %zu has taken a fork\n",
			timestamp(table->dinner_start_time), philo->id);
}
