/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:32:04 by drahwanj          #+#    #+#             */
/*   Updated: 2025/01/24 15:32:05 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <sys/time.h>
# include <errno.h>

# define F_RDLONG -99
# define RESET   "\033[0m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"
# define WHITE   "\033[37m"

typedef enum e_codes
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_codes;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_status;

typedef enum e_time
{
	MILLISECONDS,
	MICROSECONDS,
	SECONDS,
}	t_time;

/*
A smaller name for pthread_mutex_t
*/
typedef pthread_mutex_t	t_mtx;
typedef struct s_main	t_main;

typedef struct s_fork
{
	int			fork_id;
	t_mtx		fork;
}	t_fork;

typedef struct s_philo
{
	int			id;
	long		last_meal_time;
	long		meals_counter;
	bool		full;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;
	t_mtx		philo_mutex;
	t_main		*table;
}	t_philo;

typedef struct s_main
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		max_meals;
	long		philos_created;
	long		start_simulation;
	long		running_threads_number;
	bool		all_threads_ready;
	bool		end_simulation;
	bool		failure;
	pthread_t	monitor;
	t_mtx		table_mutex;
	t_mtx		print_mutex;
	t_philo		*philos;
	t_fork		*forks;
}	t_main;

/*
This function is a wrapper for the original
malloc function but prints error message.
*/
void	*ft_malloc(size_t memory);
/*
This function is a wrapper for all the
mutex functions I need through the program
with error messages.
Success Return Value: 1
Failure Return Value: 0
*/
int		ft_mutex(t_mtx *mutex, t_codes code);
/*
This function is a wrapper for all the
thread functions I need through the program
with error messages and return values.
Success Return Value: 1
Failure Return Value: 0
*/
int		ft_thread(pthread_t *thread, void *(*func)(void *),
			void *data, t_codes code);
/*
This function is designed to work only
on this program not the original atol.
*/
long	ft_atol(const char *str);
/*
Analyzes the input to check if it meets
the program requirements and assign it.
*/
bool	analyze_input(t_main *table, char **argv);
/*
Initialize the table to start working
on the simulation.
*/
bool	init_table(t_main *table);
/*
Start the simulation function!
*/
bool	start_simulation(t_main *table);
/*
Safe functions to read/set
*/
bool	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	read_bool(t_mtx *mutex, bool *value);
bool	set_long(t_mtx *mutex, long *dest, long value);
long	read_long(t_mtx *mutex, long *value);
bool	simulation_finished(t_main *table);
/*
Wait for all threads to be ready.
*/
void	wait_all_threads(t_main *table);
/*
Get time of day function.
*/
long	get_time(t_time code);
/*
Better version of usleep() function.
*/
void	smart_usleep(long usec, t_main *table);
/*
Prints the status of a philosopher
*/
bool	print_status(t_philo *philo, t_status status);

/*
Join all created threads.
*/
bool	join_all_threads(t_main *table);
void	philo_mutex_init_failure(t_philo *philo, int index);
void	mutex_init_failure(t_main *table, int index);
/*
Monitor the simulation!
*/
void	*monitor_dinner(void *data);
/*
Increases a long by 1 thread safe.
*/
bool	increase_long(t_mtx *mutex, long *value);

/*
Checks if all the threads are running or not.
*/
bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);

/*
Philo think function.
*/
void	thinking(t_philo *philo, bool pre_simulation);
/*
Desynchronize philos
*/
void	unsync(t_philo *philo);

/*
Used in smart_usleep.
*/
void	safe_usleep(long usec, t_main *table);

/*
clean function.
*/
void	clean(t_main *table);

bool	philo_died(t_philo *philo);

void	*one_philo(void	*data);

bool	failure_join(t_main *table, int index);

#endif
