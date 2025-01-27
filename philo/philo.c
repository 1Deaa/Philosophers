/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:31:44 by drahwanj          #+#    #+#             */
/*   Updated: 2025/01/24 15:31:44 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_main	table;

	if (argc == 5 || argc == 6)
	{
		if (!analyze_input(&table, argv))
		{
			printf("Error while analyzing input!\n");
			return (EXIT_FAILURE);
		}
		if (!init_table(&table))
		{
			printf("Error while initiating table!\n");
			return (EXIT_FAILURE);
		}
	}
	else
	{
		printf("Wrong input:\n./philo [%s] [%s] [%s] [%s] *[%s]\n",
			"Number of philosophers", "time_to_die", "time_to_eat",
			"time_to_sleep", "number_of_times_each_philosopher_must_eat");
		return (EXIT_FAILURE);
	}
}
