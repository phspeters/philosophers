/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:56:37 by pehenri2          #+#    #+#             */
/*   Updated: 2024/06/11 16:31:43 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

// https://nafuka11.github.io/philosophers-visualizer/

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

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
	size_t			dinner_start_time;
	size_t			is_dinner_over;
	sem_t			*dinner_over_sem;
	sem_t			*someone_died_sem;
	sem_t			*philo_is_full_sem;
	sem_t			*print_sem;
	sem_t			*forks;
	t_philo			*philo;
	pid_t			*pids;
	pthread_t		*reports;
};

struct s_philo
{
	size_t			id;
	size_t			last_meal_time;
	size_t			meals_eaten;
	sem_t			*meal_time_sem;
	t_table			*table;
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
sem_t	*start_semaphore(char *name, size_t value);
void	clean_the_table(t_table *table);
size_t	is_dinner_over(t_table *table);

/*-------------philosophers.c-------------*/

void	think(t_philo *philo);
void	eat(t_philo *philo);
void	grab_forks(t_philo *philo);
void	release_forks(t_philo *philo);
void	rest(t_philo *philo);

/*----------------dinner.c----------------*/

void	start_dinner(t_table *table);
void	sit_philosophers(t_table *table);
void	lone_diner(t_philo *philo, size_t counter);
void	dinner_routine(t_philo *philo, size_t counter);
void	end_dinner(t_table *table, t_status	status);

/*----------------waiter.c----------------*/

void	assign_waiter(t_philo *philo);
void	*check_on_philosopher(void *data);

/*-----------------host.c-----------------*/

void	manage_waiters_report(t_table *table);
void	wait_for_dinner_to_end(t_table *table);
void	*share_death_report(void *data);
void	*share_fullness_report(void *data);
void	escort_philosophers(t_table *table);

/*-----------------time.c-----------------*/

size_t	get_time_in_ms(void);
size_t	timestamp(size_t start_time);

/*----------------rules.c-----------------*/

size_t	safe_get(sem_t *semaphore, size_t *value);
void	safe_set(sem_t *semaphore, size_t *value, size_t new_value);
void	safe_print_status(t_philo *philo, t_status status);
void	print_debug(t_philo *philo, t_status status);
void	print_status(t_philo *philo, t_status status);

#endif