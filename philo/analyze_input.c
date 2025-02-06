/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:45:59 by drahwanj          #+#    #+#             */
/*   Updated: 2025/01/27 19:46:00 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	analyze_input(t_main *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1e3;
	table->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (argv[5])
	{
		table->max_meals = ft_atol(argv[5]);
		if (table->max_meals < 1)
		{
			printf("Input must be positive values!\n");
			return (false);
		}
	}
	else
		table->max_meals = 0;
	if (table->philo_nbr < 1 || table->time_to_die < 1
		|| table->time_to_eat < 1 || table->time_to_sleep < 1)
	{
		printf("Input must be positive values!\n");
		return (false);
	}
	return (true);
}

