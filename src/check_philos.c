/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:10:54 by tcali             #+#    #+#             */
/*   Updated: 2025/05/19 13:20:37 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_philos(t_philo *philo, t_data *data)
{
	t_philo	*tmp;
	int		i;

	tmp = philo;
	i = 0;
	while (i < data->nb_philo)
	{
		if (tmp->meals_eaten < data->meals)
		{
			pthread_mutex_lock(&tmp->data->print);
			ft_printf("Philo %d is doing intermitent fasting\n", tmp->id);
			pthread_mutex_unlock(&tmp->data->print);
		}
		tmp = tmp->next;
		i++;
	}
	pthread_mutex_lock(&tmp->data->print);
	ft_printf("all Philos have eaten %d times\n", data->meals);
	pthread_mutex_unlock(&tmp->data->print);
}