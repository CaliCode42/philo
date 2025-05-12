/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:49:44 by tcali             #+#    #+#             */
/*   Updated: 2025/05/12 14:41:54 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_list	*create_new_philo(t_list **philo)
{
	t_list		*new;
	t_content	current;

	if (!philo)
		return (NULL);
	current.range = 0;
	new = ft_lstnew(current);
	if (!new)
		return (NULL);
	ft_lstadd_back(philo, new);
	return (new);
}

void	init_philosophers(int total, t_list **philo)
{
	int		nb;
	t_list	*new_philo;

	nb = 1;
	new_philo = NULL;
	ft_printf("nb of philo : %d\n", total);
	while (nb <= total)
	{
		new_philo = create_new_philo(philo);
		new_philo->content.range = nb;
		ft_printf("current philo : %d\n", new_philo->content.range);
		nb++;
	}
}

int	init_data(t_data_philo *data, char **args)
{
	data->nb_philo = ft_atoi(args[1]);
	data->death = ft_atoi(args[2]);
	data->eat = ft_atoi(args[3]);
	data->sleep = ft_atoi(args[4]);
	data->meals = ft_atoi(args[5]);
	if (data->nb_philo < 1 || data->death <= 0 || data->eat <= 0
		|| data->sleep <= 0 || data->meals < 0)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_data_philo	data;
	t_list			*philo;

	if (ac != 6)
		return (ft_printf("invalid nb of args.\n"), 1);
	if (init_data(&data, av) == 0)
		return (ft_printf("Error initializing data.\n"), 1);
	philo = NULL;
	init_philosophers(data.nb_philo, &philo);
	return (0);
}
