/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:59:48 by pehenri2          #+#    #+#             */
/*   Updated: 2024/06/07 18:22:29 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	if (is_dinner_over(philo->table))
		return ;
	if (DEBUG_MODE == true)
		print_debug(philo, status);
	else
		print_status(philo, status);
}

void	print_debug(t_philo *philo, t_status status)
{
	if (status == DEAD)
		printf(RED "%zu %zu died\n" RST,
			timestamp(philo->table->dinner_start_time), philo->id);
	else if (status == THINKING)
		printf(CYN "%zu %zu is thinking\n" RST,
			timestamp(philo->table->dinner_start_time), philo->id);
	else if (status == EATING)
		printf(GRN "%zu %zu is eating for the [%zu] time\n" RST,
			timestamp(philo->table->dinner_start_time), philo->id,
			philo->meals_eaten);
	else if (status == SLEEPING)
		printf(YEL "%zu %zu is sleeping\n" RST,
			timestamp(philo->table->dinner_start_time), philo->id);
	else if (status == GRABBED_FIRST_FORK)
		printf(BLU "%zu %zu has taken his first fork\n" RST,
			timestamp(philo->table->dinner_start_time), philo->id);
	else if (status == GRABBED_SECOND_FORK)
		printf(BLU "%zu %zu has taken his second fork\n" RST,
			timestamp(philo->table->dinner_start_time), philo->id);
	else if (status == PHILO_FULL)
		printf(MAG "[%zu] is full\n" RST, philo->id);
	else if (status == EVERYONE_FULL)
		printf(MAG "All philosophers are full\n" RST);
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