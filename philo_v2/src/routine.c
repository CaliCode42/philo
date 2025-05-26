/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:32:20 by tcali             #+#    #+#             */
/*   Updated: 2025/05/26 17:42:41 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thinking(t_philo *philo)
{
	write_status(THINKING, philo, DEBUG_MODE);
}

static void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->chopstick_one->chopstick, LOCK);
	write_status(TAKE_CHOPSTICK_ONE, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->chopstick_two->chopstick, LOCK);
	write_status(TAKE_CHOPSTICK_TWO, philo, DEBUG_MODE);
	set_long(&philo->m_philo, &philo->t_last_meal, gettime(MILLISECONDS));
	philo->meals++;
	precise_usleep(philo->data->t_eat, philo->data);
	if (philo->data->nb_meals > 0
		&& philo->data->nb_meals == philo->meals)
		set_bool(&philo->m_philo, &philo->full, true);
	safe_mutex_handle(&philo->chopstick_one->chopstick, UNLOCK);
	safe_mutex_handle(&philo->chopstick_two->chopstick, UNLOCK);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->data);
	while (!end(philo->data))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->data->t_sleep, philo->data);
		thinking(philo);
	}
	return (NULL);
}

void	start_threads(t_data *data)
{
	int	i;

	i = 0;
	if (data->nb_meals == 0)
		return ;
	//else if (data->nb_philo == 1)
	//	;
	else
	{
		while (i < data->nb_philo)
		{
			safe_thread_handle(&data->philos[i].thread_id, philo_routine,
				&data->philos[i], CREATE);
			i++;
		}
	}
	data->start_time = gettime(MILLISECONDS);
	set_bool(&data->m_data, &data->threads_ready, true);
	i = 0;
	while (i < data->nb_philo)
	{
		safe_thread_handle(&data->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
}
