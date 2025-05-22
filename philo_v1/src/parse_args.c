/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:19:27 by tcali             #+#    #+#             */
/*   Updated: 2025/05/21 18:40:13 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_data *data)
{
	int	i;

	if (!data || data->nb_philo <= 0)
		return ;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return ;
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->mutex_rip, NULL);
}

int	init_data(t_data *data, int ac, char **args)
{
	data->nb_philo = ft_atoi(args[1]);
	data->death = ft_atoi(args[2]);
	data->eat = ft_atoi(args[3]);
	data->sleep = ft_atoi(args[4]);
	if (ac == 6)
		data->meals = ft_atoi(args[5]);
	else
		data->meals = 0;
	if (data->nb_philo < 1 || data->death <= 0 || data->eat <= 0
		|| data->sleep <= 0 || data->meals < 0)
		return (0);
	data->start_time = get_time_ms();
	data->rip = 0;
	init_mutexes(data);
	return (1);
}
