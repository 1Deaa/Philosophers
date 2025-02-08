/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:14:13 by drahwanj          #+#    #+#             */
/*   Updated: 2025/02/05 18:14:13 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	print_status(t_philo *philo, t_status status)
{
	long	elapsed;

	elapsed = get_time(MILLISECONDS) - philo->table->start_simulation;
	if (philo->full)
		return (true);
	if (!ft_mutex(&philo->table->print_mutex, LOCK))
		return (false);
	if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
		&& !simulation_finished(philo->table))
		printf(CYAN"%ld   %d has taken a fork\n", elapsed, philo->id);
	else if (EATING == status && !simulation_finished(philo->table))
		printf(MAGENTA"%ld   %d is eating\n"RESET, elapsed, philo->id);
	else if (SLEEPING == status && !simulation_finished(philo->table))
		printf(BLUE"%ld   %d is sleeping\n"RESET, elapsed, philo->id);
	else if (THINKING == status && !simulation_finished(philo->table))
		printf(GREEN"%ld   %d is thinking\n"RESET, elapsed, philo->id);
	else if (DIED == status && !simulation_finished(philo->table))
		printf(RED"%ld   %d died\n", elapsed, philo->id);
	if (!ft_mutex(&philo->table->print_mutex, UNLOCK))
		return (false);
	return (true);
}
