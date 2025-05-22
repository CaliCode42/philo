/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:21:14 by tcali             #+#    #+#             */
/*   Updated: 2025/05/22 17:19:04 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*philo_new(int id, t_data *data)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->meals_eaten = 0;
	philo->last_meal = 0;
	philo->thread_id = 0;
	philo->data = data;
	philo->prev = NULL;
	philo ->next = NULL;
	return (philo);
}

void	philo_add_back(t_philo **philo, t_philo *new)
{
	t_philo	*current;

	if (!philo || !new)
		return ;
	if (!*philo)
	{
		*philo = new;
		return ;
	}
	current = *philo;
	while (current->next)
		current = current->next;
	current->next = new;
	new->prev = current;
}

//t_philo	*philo_last(t_philo *philo)
//{
//	while (philo)
//	{
//		if (!philo->next)
//			return (philo);
//		philo = philo->next;
//	}
//	return (philo);
//}

t_philo	*create_new_philo(t_philo **philo, int id, t_data *data)
{
	t_philo		*new;

	if (!philo)
		return (NULL);
	new = philo_new(id, data);
	if (!new)
		return (NULL);
	philo_add_back(philo, new);
	return (new);
}

void	init_philosophers(int total, t_philo **philo, t_data *data)
{
	int		i;
	t_philo	*new_philo;

	i = 0;
	new_philo = NULL;
	//ft_printf("nb of philo : %d\n", total);
	while (i < total)
	{
		new_philo = create_new_philo(philo, i + 1, data);
		if (!new_philo)
			return ;
		//ft_printf("current philo : %d\n", new_philo->id);
		new_philo->left_fork = &data->forks[i];
		new_philo->right_fork = &data->forks[(i + 1) % total];
		pthread_mutex_init(&new_philo->thread_last_meal, NULL);
		pthread_mutex_init(&new_philo->thread_meals, NULL);
		i++;
	}
	new_philo->next = *philo;
	(*philo)->prev = new_philo;
}
