/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:49:44 by tcali             #+#    #+#             */
/*   Updated: 2025/04/29 11:15:08 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_philo_data *data, char **args)
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

int	main (int ac, char **av)
{
	t_philo_data	data;

	if (ac != 6)
		return (ft_printf("invalid nb of args.\n"), 1);
	if (init_data(&data, av) == 0)
		return (ft_printf("Error initializing data.\n"), 1);
}