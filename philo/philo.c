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
		//1)
		if (!analyze_input(&table, argv))
			return (EXIT_FAILURE);
		//2)
		init_table(&table);
		//3)
		//start_simulation(&table);
		//4)
		//clean_simulation(&table);
	}
	else
	{
		printf("Wrong input:\n./philo num time time time [num]\n");
		return (EXIT_FAILURE);
	}
}
