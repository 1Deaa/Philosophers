/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:46:17 by drahwanj          #+#    #+#             */
/*   Updated: 2025/02/05 16:46:18 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo, bool pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_simulation)
		if (!print_status(philo, THINKING))
			return ;
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	smart_usleep(t_think * 0.42, philo->table);
}

static void	eat(t_philo *philo)
{
	if (!ft_mutex(&philo->left_fork->fork, LOCK))
		return ;
	print_status(philo, TAKE_FIRST_FORK);
	if (!ft_mutex(&philo->right_fork->fork, LOCK))
		return ;
	print_status(philo, TAKE_SECOND_FORK);
	if (!set_long(&philo->philo_mutex, &philo->last_meal_time,
			get_time(MILLISECONDS)))
		return ;
	philo->meals_counter++;
	print_status(philo, EATING);
	smart_usleep(philo->table->time_to_eat, philo->table);
	if (philo->meals_counter == philo->table->max_meals
		&& philo->table->max_meals > 0)
		if (!set_bool(&philo->philo_mutex, &philo->full, true))
			return ;
	if (!ft_mutex(&philo->right_fork->fork, UNLOCK))
		return ;
	if (!ft_mutex(&philo->left_fork->fork, UNLOCK))
		return ;
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	if (read_bool(&philo->table->table_mutex, &philo->table->failure))
		return (NULL);
	if (!set_long(&philo->philo_mutex, &philo->last_meal_time,
			get_time(MILLISECONDS)))
		return (NULL);
	increase_long(&philo->table->table_mutex,
		&philo->table->running_threads_number);
	unsync(philo);
	while (!simulation_finished(philo->table))
	{
		if (read_bool(&philo->philo_mutex, &philo->full))
			break ;
		eat(philo);
		if (!print_status(philo, SLEEPING))
			return (NULL);
		smart_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, false);
	}
	return (NULL);
}

static bool	simulation_part(t_main *table)
{
	if (!ft_thread(&table->monitor, monitor_dinner, table, CREATE))
	{
		set_bool(&table->table_mutex, &table->failure, true);
		return (false);
	}
	table->start_simulation = get_time(MILLISECONDS);
	if (!set_bool(&table->table_mutex, &table->all_threads_ready, true))
		return (false);
	if (!join_all_threads(table))
	{
		philo_mutex_init_failure(table->philos, table->philo_nbr);
		return (false);
	}
	if (!set_bool(&table->table_mutex, &table->end_simulation, true))
		return (false);
	if (!ft_thread(&table->monitor, NULL, NULL, JOIN))
		return (false);
	return (true);
}

bool	start_simulation(t_main *table)
{
	int	i;

	i = -1;
	if (table->philo_nbr == 1)
	{
		if (!ft_thread(&table->philos[0].thread_id,
				one_philo, &table->philos[0], CREATE))
			return (false);
	}
	else
	{
		while (++i < table->philo_nbr)
		{
			table->philos_created++;
			if (!ft_thread(&table->philos[i].thread_id, dinner_simulation,
					&table->philos[i], CREATE))
			{
				set_bool(&table->table_mutex, &table->failure, true);
				return (false);
			}
		}
	}
	if (!simulation_part(table))
		return (false);
	return (true);
}
