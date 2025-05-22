/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:49:44 by tcali             #+#    #+#             */
/*   Updated: 2025/05/22 17:20:34 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	philo_died(t_philo *current, long now)
{
	char	*str;

	ft_sprintf(&str, "%ld %d died\n",
		now - current->data->start_time, current->id);
	thread_print(&current->data->print, &str);
	increment_thread(&current->data->mutex_rip,
		&current->data->rip, NULL, NULL);
}

void	*monitor_routine(void *arg)
{
	t_philo	*current;
	long	now;
	int		i;

	current = (t_philo *)arg;
	while (!should_stop(current))
	{
		i = 0;
		while (i++ < current->data->nb_philo)
		{
			pthread_mutex_lock(&current->thread_last_meal);
			now = get_time_ms();
			if ((now - current->last_meal) > current->data->death)
			{
				philo_died(current, now);
				return (NULL);
			}
			pthread_mutex_lock(&current->thread_last_meal);
			current = current->next;
		}
		usleep(1000);
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	char	*str;

	philo = (t_philo *)arg;
	str = NULL;
	while (!should_stop(philo))
	{
		lock_forks(philo->left_fork, philo->right_fork);
		ft_sprintf(&str, "Philo %d is eating\n", philo->id);
		increment_thread(&philo->thread_meals, &philo->meals_eaten,
			&philo->data->print, &str);
		ft_sprintf(&str, "Philo %d has eaten %d times\n",
			philo->id, philo->meals_eaten);
		thread_print(&philo->data->print, &str);
		pthread_mutex_lock(&philo->thread_last_meal);
		philo->last_meal = get_time_ms();
		pthread_mutex_unlock(&philo->thread_last_meal);
		usleep(philo->data->eat * 1000);
		unlock_forks(philo->left_fork, philo->right_fork);
		ft_sprintf(&str, "Philo %d is sleeping\n", philo->id);
		thread_print(&philo->data->print, &str);
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

	if (ac < 5 || ac > 6)
		return (ft_printf("invalid nb of args.\n"), 1);
	if (init_data(&data, ac, av) == 0)
		return (ft_printf("Error initializing data.\n"), 1);
	philo = NULL;
	init_philosophers(data.nb_philo, &philo, &data);
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
