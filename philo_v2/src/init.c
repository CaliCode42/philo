/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:19:27 by tcali             #+#    #+#             */
/*   Updated: 2025/05/26 19:54:02 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_chopsticks(t_philo *philo, t_chopstick *chopsticks, int pos)
{
	int	nb_philo;

	nb_philo = philo->data->nb_philo;
	philo->chopstick_one = &chopsticks[(pos + 1) % nb_philo];
	philo->chopstick_two = &chopsticks[pos];
	if (philo->id % 2 == 0)
	{
		philo->chopstick_one = &chopsticks[pos];
		philo->chopstick_two = &chopsticks[(pos + 1) % nb_philo];
	}
}

static void	init_philosophers(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->nb_philo)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->t_last_meal = 0;
		philo->data = data;
		philo->full = false;
		philo->meals = 0;
		safe_mutex_handle(&philo->m_philo, INIT);
		assign_chopsticks(philo, data->chopsticks, i);
		i++;
	}
}

//static void	init_mutexes(t_data *data)
//{
//	safe_mutex_handle(&data->m_eat, INIT);
//	safe_mutex_handle(&data->m_stop, INIT);
//	safe_mutex_handle(&data->m_print, INIT);
//}

void	init_data(t_data *data, char **av)
{
	int	i;

	i = 0;
	parse_input(data, av);
	data->quit = false;
	data->threads_ready = false;
	data->threads_running_nb = 0;
	data->philos = safe_malloc(sizeof(t_philo) * data->nb_philo);
	safe_mutex_handle(&data->m_data, INIT);
	data->chopsticks = safe_malloc(sizeof(t_chopstick) * data->nb_philo);
	while (i < data->nb_philo)
	{
		safe_mutex_handle(&data->chopsticks[i].chopstick, INIT);
		data->chopsticks[i].chopstick_id = i;
		i++;
	}
	init_philosophers(data);
	//init_mutexes(data);
}
