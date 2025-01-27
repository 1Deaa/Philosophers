/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:28:58 by drahwanj          #+#    #+#             */
/*   Updated: 2025/01/27 21:28:59 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_malloc(size_t memory)
{
	void	*value;

	value = malloc(memory);
	if (value == NULL)
		printf("Error while allocating memory\n");
	return (value);
}

static int	handle_mutex_errors(int exit, t_codes code)
{
	if (exit == 0)
		return (true);
	if (exit == EINVAL && (code == LOCK || code == UNLOCK))
		printf("The value specified by mutex is invalid.\n");
	else if (exit == EINVAL && code == INIT)
		printf("The value specified by attr is invalid.\n");
	else if (exit == EDEADLK)
		printf("A deadlock would occur if the thread waiting for mutex.\n");
	else if (exit == EPERM)
		printf("The current thread does not hold a lock on mutex.\n");
	else if (exit == ENOMEM)
		printf("The process cannot allocate enough memory.\n");
	else if (exit == EBUSY)
		printf("Mutex is locked!\n");
	return (false);
}

int	ft_mutex(t_mtx *mutex, t_codes code)
{
	int	ret;

	if (code == LOCK)
		ret = handle_mutex_errors(pthread_mutex_lock(mutex), code);
	else if (code == UNLOCK)
		ret = handle_mutex_errors(pthread_mutex_unlock(mutex), code);
	else if (code == INIT)
		ret = handle_mutex_errors(pthread_mutex_init(mutex, NULL), code);
	else if (code == DESTROY)
		ret = handle_mutex_errors(pthread_mutex_destroy(mutex), code);
	return (ret);
}

static int	handle_thread_errors(int exit, t_codes code)
{
	if (exit == 0)
		return (true);
	if (exit == EAGAIN)
		printf("No resources to create another thread.\n");
	else if (exit == EPERM)
		printf("The caller does not have appropriate permission.\n");
	else if (exit == EINVAL && CREATE == code)
		printf("The value specified by attr is invalid.\n");
	else if (exit == EINVAL && (code == JOIN || code == DETACH))
		printf("The value specified by thread is not joinable.\n");
	else if (exit == ESRCH)
		printf("No thread could be found corresponding to that thread ID.\n");
	else if (exit == EDEADLK)
		printf("A deadlock was detected!\n");
	return (false);
}

int	ft_thread(pthread_t *thread, void *(*func)(void *),
	void *data, t_codes code)
{
	int	ret;

	if (code == CREATE)
		ret = handle_thread_errors(pthread_create
				(thread, NULL, func, data), code);
	else if (code == JOIN)
		ret = handle_thread_errors(pthread_join(*thread, NULL), code);
	else if (code == DETACH)
		ret = handle_thread_errors(pthread_detach(*thread), code);
	return (ret);
}
