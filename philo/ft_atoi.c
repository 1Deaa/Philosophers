/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:33:37 by drahwanj          #+#    #+#             */
/*   Updated: 2025/01/24 16:33:37 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi_error(const char *str, int sign, long result)
{
	if (sign == 1 && (result > ((INT_MAX) - (*str - '0')) / 10))
		return (1);
	if (sign == -1 && (result > ((-(long)INT_MIN) - (*str - '0')) / 10))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (ft_atoi_error(str, sign, result))
			return (0);
		result = result * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (0);
	return (sign * result);
}
