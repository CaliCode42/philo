/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:35:10 by tcali             #+#    #+#             */
/*   Updated: 2025/05/28 10:56:20 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_death;

	if (get_bool(&philo->m_philo, &philo->full))
		return (false);
	elapsed = gettime(MILLISECONDS) - get_long(&philo->m_philo,
			&philo->t_last_meal);
	t_death = philo->data->t_death / 1000;
	if (elapsed > t_death)
		return (true);
	return (false);
}

//what is a spinlock ????????
void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!all_threads_running(&data->m_data, &data->threads_running_nb,
			data->nb_philo))
		;
	while (!end(data))
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (philo_died(data->philos + i) && !end(data))
			{
				set_bool(&data->m_data, &data->quit, true);
				write_status(DIED, data->philos + i, DEBUG_MODE);
			}
			i++;
		}
	}
	return (NULL);
}
