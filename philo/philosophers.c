/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 21:10:18 by pehenri2          #+#    #+#             */
/*   Updated: 2024/06/10 16:55:05 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	time_t	thinking_time;
	t_table	*table;

	table = philo->table;
	if (is_dinner_over(table))
		return ;
	safe_print_status(philo, THINKING);
	thinking_time = ((time_t)table->time_to_die - ((time_t)get_time_in_ms()
				- (time_t)philo->last_meal_time)
			- (time_t)philo->table->time_to_eat) / 2;
	if (thinking_time < 0)
		return ;
	if (thinking_time > 500)
		thinking_time = 500;
	else
	{
		while ((time_t)get_time_in_ms() < thinking_time)
		{
			if (is_dinner_over(table))
				break ;
			usleep(DEFAULT_PAUSE);
		}
	}
}

void	eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (is_dinner_over(table))
		return ;
	grab_forks(philo);
	safe_print_status(philo, EATING);
	safe_set(&philo->philo_mutex, &philo->last_meal_time, get_time_in_ms());
	while (get_time_in_ms() < safe_get(&philo->philo_mutex,
			&philo->last_meal_time) + table->time_to_eat)
	{
		if (is_dinner_over(table))
			break ;
		usleep(DEFAULT_PAUSE);
	}
	release_forks(philo);
	philo->meals_eaten++;
	if (philo->meals_eaten == table->meals_to_fullfil)
	{
		safe_print_status(philo, PHILO_FULL);
		safe_set(&philo->philo_mutex, &philo->is_full, true);
	}
}

void	grab_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork_mutex);
	safe_print_status(philo, GRABBED_FIRST_FORK);
	pthread_mutex_lock(&philo->second_fork->fork_mutex);
	safe_print_status(philo, GRABBED_SECOND_FORK);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->first_fork->fork_mutex);
	pthread_mutex_unlock(&philo->second_fork->fork_mutex);
}

void	rest(t_philo *philo)
{
	size_t	wakeup_time;
	t_table	*table;

	table = philo->table;
	if (is_dinner_over(table))
		return ;
	safe_print_status(philo, SLEEPING);
	wakeup_time = get_time_in_ms() + table->time_to_sleep;
	while (get_time_in_ms() < wakeup_time)
	{
		if (is_dinner_over(table))
			break ;
		usleep(DEFAULT_PAUSE);
	}
}
