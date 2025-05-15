/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:49:44 by tcali             #+#    #+#             */
/*   Updated: 2025/05/15 20:14:55 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->data->print);
		ft_printf("Philo %d is eating\n", philo->id);
		pthread_mutex_unlock(&philo->data->print);
		usleep(philo->data->eat * 1000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_lock(&philo->data->print);
		ft_printf("Philo %d is sleeping\n", philo->id);
		pthread_mutex_unlock(&philo->data->print);
		usleep(philo->data->sleep * 1000);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	if (ac != 6)
		return (ft_printf("invalid nb of args.\n"), 1);
	if (init_data(&data, av) == 0)
		return (ft_printf("Error initializing data.\n"), 1);
	philo = NULL;
	init_philosophers(data.nb_philo, &philo, &data);
	print_philos(philo, data.nb_philo);
	start_threads(&data, philo);
	join_threads(&data, philo);
	return (0);
}
