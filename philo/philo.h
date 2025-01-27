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

typedef pthread_mutex_t t_mtx;
typedef struct s_main t_main;

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
	t_philo	*philo;
	t_fork	*fork;
}	t_main;

long	ft_atol(const char *str);
bool	analyze_input(t_main *table, char **argv);

#endif