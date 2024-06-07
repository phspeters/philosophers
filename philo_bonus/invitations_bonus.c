/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invitations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 21:03:26 by pehenri2          #+#    #+#             */
/*   Updated: 2024/06/07 17:50:18 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	check_invitations_details(int argc, char **argv)
{
	char	**arguments;

	if (!is_valid_argument_number(argc))
		return (false);
	arguments = argv + 1;
	while (*arguments)
	{
		if (!is_valid_string(*arguments))
			return (false);
		if (!is_valid_range(*arguments))
			return (false);
		arguments++;
	}
	if (!within_philo_limit(argv[1]))
		return (false);
	return (true);
}

bool	is_valid_argument_number(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: Correct usage: ./philo 'number_of_philosophers'\
 'time_to_die' 'time_to_eat' 'time_to_sleep' [number_of_times_each_\
 philosopher_must_eat]\n-> Times are in milliseconds and the last\
  argument is optional\n");
		return (false);
	}
	return (true);
}

bool	is_valid_string(char *argv)
{
	while (*argv)
	{
		if ((*argv) > '9' || (*argv) < '0')
		{
			printf("Error: Invalid input. All arguments should consist of\
 only digits.\n");
			return (false);
		}
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
	else if (counter == 10)
	{
		counter = 0;
		while (argv[counter] && "2147483647"[counter])
		{
			if (argv[counter] > "2147483647"[counter])
				break ;
			counter++;
		}
		if (counter != 10)
		{
			printf("Error: Invalid input. Argument values should not\
 exceed the maximum integer value\n");
			return (false);
		}
	}
	return (true);
}

bool	within_philo_limit(char *argv)
{
	size_t	philos_count;

	philos_count = string_to_size_t(argv);
	if (philos_count < 1)
	{
		printf("Error: Invalid input. Number of philosophers should be\
 greater than 0\n");
		return (false);
	}
	if (philos_count > MAX_PHILOS)
	{
		printf("Error: Chill out, you're going to freeze the system. If\
 you're sure of what you're doing, change the MAX_PHILOS macro in the philo.h\
 file.\nCurrent max: %d\n", MAX_PHILOS);
		return (false);
	}
	return (true);
}
