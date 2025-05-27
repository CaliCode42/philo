/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:32:20 by tcali             #+#    #+#             */
/*   Updated: 2025/05/27 15:49:44 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->data);
	set_long(&philo->m_philo, &philo->t_last_meal, gettime(MILLISECONDS));
	increase_long(&philo->m_philo, &philo->data->threads_running_nb);
	write_status(TAKE_CHOPSTICK_ONE, philo, DEBUG_MODE);
	while (!end(philo->data))
		usleep(200);
	return (NULL);
}

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
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->data->t_eat, philo->data);
	if (philo->data->nb_meals > 0
		&& philo->data->nb_meals == philo->meals)
	{
		set_bool(&philo->m_philo, &philo->full, true);
		write_status(FULL, philo, DEBUG_MODE);
	}
	safe_mutex_handle(&philo->chopstick_one->chopstick, UNLOCK);
	safe_mutex_handle(&philo->chopstick_two->chopstick, UNLOCK);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->data);
	set_long(&philo->m_philo, &philo->t_last_meal, gettime(MILLISECONDS));
	increase_long(&philo->data->m_data, &philo->data->threads_running_nb);
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
	else if (data->nb_philo == 1)
		safe_thread_handle(&data->philos[0].thread_id, one_philo,
			&data->philos[0], CREATE);
	else
	{
		while (i < data->nb_philo)
		{
			safe_thread_handle(&data->philos[i].thread_id, philo_routine,
				&data->philos[i], CREATE);
			i++;
		}
	}
	safe_thread_handle(&data->monitor, monitor_routine, data, CREATE);
	data->start_time = gettime(MILLISECONDS);
	set_bool(&data->m_data, &data->threads_ready, true);
	i = 0;
	while (i < data->nb_philo)
	{
		safe_thread_handle(&data->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
	set_bool(&data->m_data, &data->quit, true);
	safe_thread_handle(&data->monitor, NULL, NULL, JOIN);
}
