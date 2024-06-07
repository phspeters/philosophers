/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:41:59 by pehenri2          #+#    #+#             */
/*   Updated: 2024/06/07 18:23:37 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// iniciar monitoramento antes do start dinner ou entao criar todos os philos
// e iniciar o cronometro logo antes de ligar a flag de todos sentados?
/*
 * argv[1] = number_of_philosophers
 * argv[2] = time_to_die -> time to spend without eating
 * argv[3] = time_to_eat -> time to spend eating
 * argv[4] = time_to_sleep -> time to spend sleeping
 * argv[5] = [number_of_times_each_philosopher_must_eat] -> optional
 */
int	main(int argc, char **argv)
{
	t_table	table;

	if (check_invitations_details(argc, argv))
	{
		set_table(&table, argv);
		welcome_philosophers(&table);
		start_dinner(&table);
		while (!is_dinner_over(&table))
			check_on_philosophers(&table);
		escort_philosophers(&table);
		clean_the_table(&table);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
