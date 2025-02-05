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
		if (!start_simulation(&table))
		{
			printf("Error while simulation\n");
			return (EXIT_FAILURE);
		}
		//Clean simulation(4).
	}
	else
	{
		printf("Wrong input:\n./philo [%s] [%s] [%s] [%s] *[%s]*\n",
			"philosophers", "die", "eat",
			"sleep", "meals_must_eat");
		return (EXIT_FAILURE);
	}
}
