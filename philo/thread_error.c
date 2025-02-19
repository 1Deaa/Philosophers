/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:21:08 by drahwanj          #+#    #+#             */
/*   Updated: 2025/02/19 16:21:09 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	failure_join(t_main *table, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (!ft_thread(&table->philos[i].thread_id, NULL, NULL, JOIN))
		{
			return (false);
		}
		i++;
	}
	return (true);
}
