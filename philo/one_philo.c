/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:28:18 by drahwanj          #+#    #+#             */
/*   Updated: 2025/02/08 22:28:19 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(void	*data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECONDS));
	increase_long(&philo->table->table_mutex,
		&philo->table->running_threads_number);
	print_status(philo, TAKE_FIRST_FORK);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}
