/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 21:10:18 by pehenri2          #+#    #+#             */
/*   Updated: 2024/06/05 21:18:17 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	time_t	thinking_time;
	t_table	*table;

	safe_print_status(philo, THINKING);
	table = philo->table;
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
	grab_forks(philo);
	safe_print_status(philo, EATING);
	safe_set(philo->philo_turn, &philo->last_meal_time, get_time_in_ms());
	usleep(philo->table->time_to_eat * 1000);
	release_forks(philo);
	philo->meals_eaten++;
	if (philo->meals_eaten == table->meals_to_fullfil)
		sem_post(table->philo_is_full);
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
	safe_print_status(philo, SLEEPING);
	usleep(table->time_to_sleep * 1000);
}
