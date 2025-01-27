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
	t_main		*table;
}	t_philo;

typedef struct s_main
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		max_meals;
	long		start_simulation;
	bool		end_simulation;
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

#endif