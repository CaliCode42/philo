/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:04:05 by tcali             #+#    #+#             */
/*   Updated: 2025/05/26 19:56:04 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		error_exit("Error allocating memory.");
	return (ret);
}

static void	handle_mutex_error(int status, t_opcode opcode)
{
	char	*enomem;

	enomem = "The process cannot allocate enough mem to create another mutex.";
	if (status == 0)
		return ;
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		error_exit("The value specified by mutex is invalid.");
	else if (status == EINVAL && opcode == INIT)
		error_exit("The value specified by attr is invalid.");
	else if (status == EDEADLK)
		error_exit("A deadlock was detected.");
	else if (status == EPERM)
		error_exit("the current thread does not hold a lock on mutex.");
	else if (status == ENOMEM)
		error_exit(enomem);
	else if (status == EBUSY)
		error_exit("Mutex is locked.");
}

void	*safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Wrong opcode for mutex handle.");
	return (NULL);
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	else if (status == EAGAIN)
		error_exit("Insufficient resources to create another thread.");
	else if (status == EPERM)
		error_exit("The caller does not have appropriate permissions.");
	else if (status == EDEADLK)
		error_exit("A deadlock was detected.");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		error_exit ("Thread is not joinable.");
	else if (status == ESRCH)
		error_exit("Thread id not found.");
}

void	safe_thread_handle(pthread_t *thread, void *(*f)(void *),
		void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, f, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("Wrong opcode for thread handle.");
}
