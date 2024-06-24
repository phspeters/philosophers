/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:56:37 by pehenri2          #+#    #+#             */
/*   Updated: 2024/06/24 14:20:29 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

# define DEFAULT_PAUSE 1000
# define MAX_PHILOS 200

# define BLU "\033[0;34m"
# define GRN "\033[0;32m"
# define CYN "\033[0;36m"
# define YEL "\033[0;33m"
# define RED "\033[0;31m"
# define MAG "\033[0;35m"
# define RST "\033[0m"

typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;
typedef struct s_table	t_table;
typedef enum e_status	t_status;

struct s_table
{
	size_t			philo_count;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			meals_to_fullfil;
	size_t			all_philos_ready;
	size_t			dinner_start_time;
	size_t			dinner_is_over;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	print_mutex;
	t_fork			*forks;
	t_philo			*philos;
};

struct s_philo
{
	size_t			id;
	pthread_t		thread_id;
	pthread_mutex_t	philo_mutex;
	size_t			last_meal_time;
	size_t			meals_eaten;
	size_t			is_full;
	t_fork			*first_fork;
	t_fork			*second_fork;
	t_table			*table;
};

struct s_fork
{
	size_t			id;
	pthread_mutex_t	fork_mutex;
};

enum				e_status
{
	DEAD,
	THINKING,
	EATING,
	SLEEPING,
	GRABBED_FIRST_FORK,
	GRABBED_SECOND_FORK,
	PHILO_FULL,
	EVERYONE_FULL,
};

/*-------------invitations.c--------------*/

bool	check_invitations_details(int argc, char **argv);
bool	is_valid_argument_number(int argc);
bool	is_valid_string(char *argv);
bool	is_valid_range(char *argv);
bool	within_philo_limit(char *argv);

/*----------------table.c-----------------*/

void	set_table(t_table *table, char **argv);
size_t	string_to_size_t(const char *str);
void	welcome_philosophers(t_table *table);
void	assign_forks(t_table *table, size_t philo_pos);
void	clean_the_table(t_table *table);

/*-------------philosophers.c-------------*/

void	think(t_philo *philo);
void	eat(t_philo *philo);
void	grab_forks(t_philo *philo);
void	release_forks(t_philo *philo);
void	rest(t_philo *philo);

/*----------------dinner.c----------------*/

void	start_dinner(t_table *table);
void	sit_philosophers(t_table *table);
void	*lone_diner(void *data);
void	*dinner_routine(void *data);
void	wait_for_all_philos_to_sit(t_table *table);

/*-----------------host.c-----------------*/

void	check_on_philosophers(t_table *table);
void	escort_philosophers(t_table *table);
bool	is_dinner_over(t_table *table);

/*-----------------time.c-----------------*/

size_t	get_time_in_ms(void);
size_t	timestamp(size_t start_time);

/*----------------rules.c-----------------*/

size_t	safe_get(pthread_mutex_t *mutex, size_t *value);
void	safe_set(pthread_mutex_t *mutex, size_t *value, size_t new_value);
void	safe_print_status(t_philo *philo, t_status status);
void	print_debug(t_philo *philo, t_status status);
void	print_status(t_philo *philo, t_status status);

#endif