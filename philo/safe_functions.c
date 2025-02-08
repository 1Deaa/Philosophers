/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:07:52 by drahwanj          #+#    #+#             */
/*   Updated: 2025/02/05 17:07:53 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	if (!ft_mutex(mutex, LOCK))
		return (false);
	*dest = value;
	if (!ft_mutex(mutex, UNLOCK))
		return (false);
	return (true);
}

bool	read_bool(t_mtx *mutex, bool *value)
{
	bool	ret;

	if (!ft_mutex(mutex, LOCK))
		return (false);
	ret = *value;
	if (!ft_mutex(mutex, UNLOCK))
		return (false);
	return (ret);
}

bool	set_long(t_mtx *mutex, long *dest, long value)
{
	if (!ft_mutex(mutex, LOCK))
		return (false);
	*dest = value;
	if (!ft_mutex(mutex, UNLOCK))
		return (false);
	return (true);
}

long	read_long(t_mtx *mutex, long *value)
{
	long	ret;

	if (!ft_mutex(mutex, LOCK))
		return (F_RDLONG);
	ret = *value;
	if (!ft_mutex(mutex, UNLOCK))
		return (F_RDLONG);
	return (ret);
}

bool	simulation_finished(t_main *table)
{
	bool	result;

	result = read_bool(&table->table_mutex, &table->end_simulation);
	return (result);
}
