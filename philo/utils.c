/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:39:49 by drahwanj          #+#    #+#             */
/*   Updated: 2025/02/05 17:39:50 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_time code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	if (SECONDS == code)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (MILLISECONDS == code)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (MICROSECONDS == code)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	return (-1);
}

void	smart_usleep(long usec, t_main *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = (get_time(MICROSECONDS));
	while ((get_time(MICROSECONDS)) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = (get_time(MICROSECONDS)) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			safe_usleep(rem / 2, table);
		else
		{
			while ((get_time(MICROSECONDS)) - start < usec)
				;
		}
	}
}

bool	join_all_threads(t_main *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		if (!ft_thread(&table->philos[i].thread_id, NULL, NULL, JOIN))
		{
			return (false);
		}
	}
	return (true);
}

void	philo_mutex_init_failure(t_philo *philo, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (!ft_mutex(&philo->philo_mutex, DESTROY))
			printf("Failed to destroy mutex %d!\n", i);
		i++;
	}
	mutex_init_failure(philo->table, philo->table->philo_nbr);
}

bool	increase_long(t_mtx *mutex, long *value)
{
	if (!ft_mutex(mutex, LOCK))
		return (false);
	(*value)++;
	if (!ft_mutex(mutex, UNLOCK))
		return (false);
	return (true);
}
