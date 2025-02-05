/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:34:10 by drahwanj          #+#    #+#             */
/*   Updated: 2025/02/05 17:34:10 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_main *table)
{
    while (!read_bool(&table->table_mutex, &table->all_threads_ready))
        ;
}

bool    all_threads_running(t_mtx *mutex, long *threads, long philo_nbr)
{
    bool    ret;

    ret = false;
    if (!ft_mutex(mutex, LOCK))
        return (false);
    if (*threads == philo_nbr)
        ret = true;
    if (!ft_mutex(mutex, UNLOCK))
        return (false);
    return (ret);
}

