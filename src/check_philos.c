/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:10:54 by tcali             #+#    #+#             */
/*   Updated: 2025/05/20 17:30:06 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//fct to check if all philos have eaten, if yes returns (1), else returns (0).
int	check_philos(t_philo *philo, t_data *data)
{
	t_philo	*tmp;
	int		i;

	tmp = philo;
	i = 0;
	while (i < data->nb_philo)
	{
		if (data->meals && tmp->meals_eaten < data->meals)
		{
			return (0);
		}
		tmp = tmp->next;
		i++;
	}
	ft_printf("all Philos have eaten %d times\n", data->meals);
	return (1);
}

int	should_stop(t_philo *philo)
{
	int	stop;

	pthread_mutex_lock(&philo->data->mutex_rip);
	stop = philo->data->rip;
	pthread_mutex_unlock(&philo->data->mutex_rip);
	return (stop);
}
