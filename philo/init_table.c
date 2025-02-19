/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:11:53 by drahwanj          #+#    #+#             */
/*   Updated: 2025/01/27 21:11:54 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_init_failure(t_main *table, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (!ft_mutex(&table->forks[i].fork, DESTROY))
			printf("Failed to destroy mutex %d!\n", i);
		i++;
	}
	free(table->forks);
	free(table->philos);
}

static void	assign_forks(t_philo *philo, t_fork *forks, int pos)
{
	if (philo->id % 2 == 0)
	{
		philo->right_fork = &forks[pos];
		philo->left_fork = &forks[(pos + 1) % philo->table->philo_nbr];
	}
	else
	{
		philo->right_fork = &forks[(pos + 1) % philo->table->philo_nbr];
		philo->left_fork = &forks[pos];
	}
}

static bool	philo_init(t_main *table)
{
	int		i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		table->philos[i].id = i + 1;
		table->philos[i].full = false;
		table->philos[i].meals_counter = 0;
		table->philos[i].table = table;
		table->philos[i].last_meal_time = 0;
		if (!ft_mutex(&table->philos[i].philo_mutex, INIT))
		{
			philo_mutex_init_failure(table->philos, i);
			return (false);
		}
		assign_forks(&table->philos[i], table->forks, i);
	}
	return (true);
}

static bool	forks_init(t_main *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		if (!ft_mutex(&table->forks[i].fork, INIT))
		{
			mutex_init_failure(table, i);
			return (false);
		}
		table->forks[i].fork_id = i;
	}
	return (true);
}

bool	init_table(t_main *table)
{
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->failure = false;
	table->running_threads_number = 0;
	table->philos_created = 0;
	table->philos = calloc(sizeof(t_philo) * table->philo_nbr, 1);
	if (!ft_mutex(&table->table_mutex, INIT))
		return (false);
	if (!ft_mutex(&table->print_mutex, INIT))
		return (false);
	if (!(table->philos))
		return (false);
	table->forks = ft_malloc(sizeof(t_fork) * table->philo_nbr);
	if (!(table->forks))
	{
		free(table->philos);
		return (false);
	}
	if (!forks_init(table))
		return (false);
	if (!philo_init(table))
		return (false);
	return (true);
}
