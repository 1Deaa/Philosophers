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

void	*one_philo(void	*data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILLISECONDS));
	increase_long(&philo->table->table_mutex, &philo->table->running_threads_number);
	print_status(philo, TAKE_FIRST_FORK);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}

static void	thinking(t_philo *philo)
{
	if (!print_status(philo, THINKING))
		return ;
}

static void	eat(t_philo *philo)
{
	if (!ft_mutex(&philo->left_fork->fork, LOCK))
		return ;
	if (!print_status(philo, TAKE_FIRST_FORK))
		return ;
	if (!ft_mutex(&philo->right_fork->fork, LOCK))
		return ;
	if (!print_status(philo, TAKE_SECOND_FORK))
		return ;
	if (!set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILLISECONDS)))
		return ;
	if (!set_long(&philo->philo_mutex, &philo->meals_counter, philo->meals_counter + 1))
		return ;
	if (!print_status(philo, EATING))
		return ;
	smart_usleep(philo->table->time_to_eat, philo->table);
	if (philo->meals_counter == philo->table->max_meals && philo->table->max_meals > 0)
		if (!set_bool(&philo->philo_mutex, &philo->full, true))
			return ;
	if (!ft_mutex(&philo->right_fork->fork, UNLOCK))
		return ;
	if (!ft_mutex(&philo->left_fork->fork, UNLOCK))
		return ;
}

void	*dinner_simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	if (!set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILLISECONDS)))
		return (NULL);
	increase_long(&philo->table->table_mutex, &philo->table->running_threads_number);
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break;
		eat(philo);
		if (!print_status(philo, SLEEPING))
			return (NULL);
		smart_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo);
	}
	return (NULL);
}

bool    start_simulation(t_main *table)
{
	int i;

	i = -1;
	if (table->philo_nbr == 1)
	{
		if (!ft_thread(&table->philos[0].thread_id, one_philo, &table->philos[0], CREATE))
			return (false);
	}
	else
	{
		while (++i < table->philo_nbr)
		{
			if (!ft_thread(&table->philos[i].thread_id, dinner_simulation,
				&table->philos[i], CREATE))
			{
				printf("Thread creation failed");
				return (false);
			}
		}
	}
	if (!ft_thread(&table->monitor, monitor_dinner, table, CREATE))
	{
		mutex_init_failure(table, table->philo_nbr);
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
	return (true);
}
