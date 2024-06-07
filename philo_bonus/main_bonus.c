/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:41:59 by pehenri2          #+#    #+#             */
/*   Updated: 2024/06/07 17:50:18 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
 * argv[1] = number_of_philosophers
 * argv[2] = time_to_die -> time to spend without eating
 * argv[3] = time_to_eat -> time to spend eating
 * argv[4] = time_to_sleep -> time to spend sleeping
 * argv[5] = [number_of_times_each_philosopher_must_eat] -> optional
 */
// idea: put every helper function in tools.c?
int	main(int argc, char **argv)
{
	t_table	table;

	if (check_invitations_details(argc, argv))
	{
		set_table(&table, argv);
		manage_waiters(&table);
		start_dinner(&table);
		wait_for_dinner_to_end(&table);
		clean_the_table(&table);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
