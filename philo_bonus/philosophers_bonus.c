/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 21:10:18 by pehenri2          #+#    #+#             */
/*   Updated: 2024/06/10 16:56:56 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	usleep(thinking_time * 1000);
}

void	eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (is_dinner_over(table))
		return ;
	grab_forks(philo);
	safe_set(philo->meal_time_sem, &philo->last_meal_time, get_time_in_ms());
	philo->meals_eaten++;
	safe_print_status(philo, EATING);
	usleep(philo->table->time_to_eat * 1000);
	release_forks(philo);
	if (philo->meals_eaten == table->meals_to_fullfil)
	{
		sem_post(table->philo_is_full_sem);
		safe_print_status(philo, PHILO_FULL);
	}
}

void	grab_forks(t_philo *philo)
{
	sem_wait(philo->table->forks);
	safe_print_status(philo, GRABBED_FIRST_FORK);
	sem_wait(philo->table->forks);
	safe_print_status(philo, GRABBED_SECOND_FORK);
}

void	release_forks(t_philo *philo)
{
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
}

void	rest(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (is_dinner_over(table))
		return ;
	safe_print_status(philo, SLEEPING);
	usleep(table->time_to_sleep * 1000);
}
