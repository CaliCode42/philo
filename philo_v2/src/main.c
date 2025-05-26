/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:01:16 by tcali             #+#    #+#             */
/*   Updated: 2025/05/26 19:09:53 by tcali            ###   ########.fr       */
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
		safe_mutex_handle(&data->philos[i].chopstick_one->chopstick, DESTROY);
		safe_mutex_handle(&data->philos[i].chopstick_two->chopstick, DESTROY);
		//safe_mutex_handle(&data->philos[i].mutex_meals, DESTROY);
		//safe_mutex_handle(&data->philos[i].mutex_last_meal, DESTROY);
		i++;
	}
	free(data->philos);
	safe_mutex_handle(&data->m_print, DESTROY);
	safe_mutex_handle(&data->m_eat, DESTROY);
	safe_mutex_handle(&data->m_stop, DESTROY);
}

int	main(int ac, char **av)
{
	t_data		data;

	if (ac < 5 || ac > 6)
		error_exit("invalid nb of args.");
	init_data(&data, av);
	start_threads(&data);
	free_destroy(&data);
	return (0);
}
