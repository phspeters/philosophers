/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:59:48 by pehenri2          #+#    #+#             */
/*   Updated: 2024/05/30 21:19:09 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	safe_get(pthread_mutex_t *mutex, size_t *value)
{
	size_t	get_value;

	pthread_mutex_lock(mutex);
	get_value = *value;
	pthread_mutex_unlock(mutex);
	return (get_value);
}

void	safe_set(pthread_mutex_t *mutex, size_t *value, size_t new_value)
{
	pthread_mutex_lock(mutex);
	*value = new_value;
	pthread_mutex_unlock(mutex);
}

void	safe_print_status(t_philo *philo, t_status status)
{
	t_table	*table;

	table = philo->table;
	if (is_dinner_over(table))
		return ;
	pthread_mutex_lock(&table->print_mutex);
	if (DEBUG_MODE == true)
		print_debug(philo, status);
	else
		print_status(philo, status);
	pthread_mutex_unlock(&table->print_mutex);
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
		printf("%zu %zu has taken his first fork [%zu]\n",
			timestamp(table->dinner_start_time), philo->id,
			philo->first_fork->id);
	else if (status == GRABBED_SECOND_FORK)
		printf("%zu %zu has taken his second fork [%zu]\n",
			timestamp(table->dinner_start_time), philo->id,
			philo->second_fork->id);
	else if (status == EVERYONE_FULL)
		printf("All philosophers are full\n");
}

void	print_status(t_philo *philo, t_status status)
{
	t_table	*table;

	table = philo->table;
	if (is_dinner_over(table))
		return ;
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
