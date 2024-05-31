/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invitations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 21:03:26 by pehenri2          #+#    #+#             */
/*   Updated: 2024/05/30 20:11:33 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_invitations_details(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (!printf("Error: Invalid number of arguments\n\tCorrect usage:\
 ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
 [number_of_times_each_philosopher_must_eat]\n\tTimes are in milliseconds and the\
 last argument is optional\n"));
	while (*argv)
	{
		if (!is_valid_string(*argv))
			return (!printf("Error: Invalid input. All arguments should contain\
 only digits.\n"));
		if (!is_valid_range(*argv))
			return (!printf("Error: Invalid input. Argument values should not\
 exceed the maximum integer value\n"));
		argv++;
	}
	return (true);
}

bool	is_valid_string(char *argv)
{
	while (*argv)
	{
		if ((*argv) > '9' || (*argv) < '0')
			return (false);
		argv++;
	}
	return (true);
}

bool	is_valid_range(char *argv)
{
	int	counter;

	counter = 0;
	while (argv[counter])
		counter++;
	if (counter > 10)
		return (false);
	if (counter == 10)
	{
		counter = 0;
		while (argv[counter] && "2147483647"[counter])
		{
			if (argv[counter] > "2147483647"[counter])
				return (false);
			counter++;
		}
	}
	return (true);
}
