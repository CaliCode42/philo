/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:21:14 by tcali             #+#    #+#             */
/*   Updated: 2025/05/15 20:14:53 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_threads(t_data *data, t_philo *philo)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	tmp = philo;
	while (i < data->nb_philo)
	{
		pthread_create(&tmp->thread_id, NULL, &philo_routine, tmp);
		tmp = tmp->next;
		i++;
	}
}

void	join_threads(t_data *data, t_philo *philo)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	tmp = philo;
	while (i < data->nb_philo)
	{
		pthread_join(tmp->thread_id, NULL);
		tmp = tmp->next;
		i++;
	}
}
