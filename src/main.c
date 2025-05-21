/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:49:44 by tcali             #+#    #+#             */
/*   Updated: 2025/05/21 16:58:25 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	*monitor_routine(void *arg)
{
	t_philo	*start;
	t_philo	*current;
	long	now;
	int		i;

	start = (t_philo *)arg;
	current = start;
	while (!should_stop(current))
	{
		i = 0;
		while (i < start->data->nb_philo)
		{
			now = get_time_ms();
			if ((now - current->last_meal) > current->data->death)
			{
				pthread_mutex_lock(&current->data->print);
				ft_printf("%ld %d died\n",
					now - current->data->start_time, current->id);
				pthread_mutex_unlock(&current->data->print);
				pthread_mutex_lock(&current->data->mutex_rip);
				current->data->rip = 1;
				pthread_mutex_unlock(&current->data->mutex_rip);
				return (NULL);
			}
			current = current->next;
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!should_stop(philo))
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->data->print);
		ft_printf("Philo %d is eating\n", philo->id);
		philo->meals_eaten++;
		ft_printf("Philo %d has eaten %d times\n",
			philo->id, philo->meals_eaten);
		pthread_mutex_unlock(&philo->data->print);
		philo->last_meal = get_time_ms();
		usleep(philo->data->eat * 1000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_lock(&philo->data->print);
		ft_printf("Philo %d is sleeping\n", philo->id);
		pthread_mutex_unlock(&philo->data->print);
		usleep(philo->data->sleep * 1000);
		if (philo->data->meals && philo->meals_eaten == philo->data->meals)
			break ;
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_philo		*philo;
	pthread_t	monitor;

	if (ac != 6)
		return (ft_printf("invalid nb of args.\n"), 1);
	if (init_data(&data, av) == 0)
		return (ft_printf("Error initializing data.\n"), 1);
	philo = NULL;
	init_philosophers(data.nb_philo, &philo, &data);
	//print_philos(philo, data.nb_philo);
	start_threads(&data, philo);
	pthread_create(&monitor, NULL, &monitor_routine, philo);
	join_threads(&data, philo);
	pthread_join(monitor, NULL);
	if (check_philos(philo, &data) == 0)
	{
		ft_printf("Some philosophers did not eat enough.\n");
		return (1);
	}
	return (0);
}
