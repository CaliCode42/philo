/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:19:27 by tcali             #+#    #+#             */
/*   Updated: 2025/05/23 16:47:52 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_meal = 0;
		data->philo[i].right_chopstick = NULL;
		data->philo[i].data = data;
		data->philo[i].meals = 0;
		pthread_mutex_init(&(data->philo[i].left_chopstick), NULL);
		if (i == data->nb_philo - 1)
			data->philo[i].right_chopstick = &data->philo[0].left_chopstick;
		else
			data->philo[i].right_chopstick = &data->philo[i + 1].left_chopstick;
		if (pthread_create(&data->philo[i].thread_id, NULL, \
				&philo_routine, &(data->philo[i])) != 0)
			return (-1);
		i++;
	}
	i = -1;
	while (++i < data->nb_philo)
		if (pthread_join(data->philo[i].thread_id, NULL) != 0)
			return (-1);
	return (0);
}

void	init_mutexes(t_data *data)
{
	pthread_mutex_init(&data->mutex_eat, NULL);
	pthread_mutex_init(&data->mutex_stop, NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->mutex_rip, NULL);
}

int	init_data(t_data *data, int ac, char **args)
{
	init_mutexes(data);
	data->nb_philo = ft_atoi(args[1]);
	data->t_death = ft_atoi(args[2]);
	data->t_eat = ft_atoi(args[3]);
	data->t_sleep = ft_atoi(args[4]);
	if (ac == 6)
		data->nb_meals = ft_atoi(args[5]);
	else
		data->nb_meals = 0;
	if (data->nb_philo < 1 || data->t_death <= 0 || data->t_eat <= 0
		|| data->t_sleep <= 0 || data->nb_meals < 0)
		return (0);
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return ;
	data->start_time = get_time_ms();
	data->rip = 0;
	return (1);
}
