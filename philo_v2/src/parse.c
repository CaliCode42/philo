/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:19:49 by tcali             #+#    #+#             */
/*   Updated: 2025/06/04 16:41:40 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("input must be only positive values.");
	if (!is_digit(*str))
		error_exit("invalid input.");
	number = str;
	while (is_digit(*str++))
		++len;
	if (len >= 10)
		error_exit("input must be <= INT_MAX");
	return (number);
}

static long	ft_atol(const char *str)
{
	long	nb;

	nb = 0;
	str = valid_input(str);
	while (is_digit(*str))
		nb = (nb * 10) + (*str++ - 48);
	if (nb > INT_MAX)
		error_exit("input must be <= INT_MAX");
	return (nb);
}

void	parse_input(t_data *data, char **av)
{
	data->nb_philo = ft_atol(av[1]);
	data->t_death = ft_atol(av[2]) * 1e3;
	data->t_eat = ft_atol(av[3]) * 1e3;
	data->t_sleep = ft_atol(av[4]) * 1e3;
	if (data->t_death < 6e4 || data->t_eat < 6e4 || data->t_sleep < 6e4)
		error_exit("timestamp must be >= 60ms");
	if (av[5])
		data->nb_meals = ft_atol(av[5]);
	else
		data->nb_meals = -1;
}
