/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:27:32 by tcali             #+#    #+#             */
/*   Updated: 2025/05/28 11:27:39 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_data *data)
{
	while (!get_bool(&data->m_data, &data->threads_ready))
		;
}

void	increase_long(t_mtx *mutex, long *value)
{
	safe_mutex_handle(mutex, LOCK);
	(*value)++;
	safe_mutex_handle(mutex, UNLOCK);
}

void	de_sync_philos(t_philo *philo)
{
	if (philo->data->nb_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(30000, philo->data);
	}
	else
	{
		if (philo->id % 2 == 0)
			thinking(philo, false);
	}
}

bool	all_threads_running(t_mtx *mutex, long *threads,
	long philo_nb)
{
	bool	ret;

	ret = false;
	safe_mutex_handle(mutex, LOCK);
	if (*threads == philo_nb)
		ret = true;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}
