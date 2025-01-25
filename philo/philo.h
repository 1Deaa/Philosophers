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

int		ft_atoi(const char *str);
bool	is_wrong_args(int argc, char **argv);

typedef struct s_fork
{
	int					fork_id;
	pthread_mutex_t		fork;
}	t_fork;

typedef struct s_philo
{
	int			id;
	int			last_meal_time;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;
}	t_philo;

typedef struct s_main
{
	int		philo_nbr;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	t_philo	*philo;
	t_fork	*fork;
}	t_main;

#endif