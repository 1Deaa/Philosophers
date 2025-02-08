/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 23:14:33 by drahwanj          #+#    #+#             */
/*   Updated: 2025/02/05 23:14:34 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (read_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = get_time(MILLISECONDS) - read_long(&philo->philo_mutex, &philo->last_meal_time);
	t_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	t_main	*table;
	int		i;

	table = (t_main *)data;
	while (!all_threads_running(&table->table_mutex,
		&table->running_threads_number, table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while ((++i < table->philo_nbr) && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				if (!print_status(table->philos + i, DIED))
					return (NULL);
				if (!set_bool(&table->table_mutex, &table->end_simulation, true))
					return (NULL);
			}
		}
	}
	return (NULL);
}