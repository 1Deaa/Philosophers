/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:28:03 by drahwanj          #+#    #+#             */
/*   Updated: 2025/02/08 18:28:04 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_main *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		ft_mutex(&philo->philo_mutex, DESTROY);
		i++;
	}
	ft_mutex(&table->print_mutex, DESTROY);
	ft_mutex(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}
