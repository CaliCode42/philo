/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:01:16 by tcali             #+#    #+#             */
/*   Updated: 2025/05/23 16:49:19 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//To make this project more logic and respectful towards Italian people, I
//choose to make my philosophers eat a bowl of noodles, with chopsticks. Each 
//philosopher has only one chopstick.
//Since it's really not easy to eat noodles with only one chopstick it makes
//more sense to me to justify the need of using the neighbor's chopstick.

void	free_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->philo[i].left_chopstick);
		pthread_mutex_destroy(data->philo[i].right_chopstick);
		pthread_mutex_destroy(&data->philo[i].thread_id);
		pthread_mutex_destroy(&data->philo[i].mutex_meals);
		pthread_mutex_destroy(&data->philo[i].mutex_last_meal);
	}
	free(data->philo);
	pthread_mutex_destroy(&data->mutex_rip);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->mutex_eat);
	pthread_mutex_destroy(&data->mutex_stop);
}

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	monitor;

	if (ac < 5 || ac > 6)
		return (ft_printf("invalid nb of args.\n"), 1);
	if (init_data(&data, ac, av) == 0)
		return (ft_printf("Error initializing data.\n"), 1);
	init_philosophers(data.nb_philo, &data);
	start_threads(&data);
	pthread_create(&monitor, NULL, &monitor_routine);
	join_threads(&data, philo);
	pthread_join(monitor, NULL);
	free_destroy(&data);
	return (0);
}
