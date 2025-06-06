/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:45:59 by tcali             #+#    #+#             */
/*   Updated: 2025/05/28 11:55:42 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed.");
	if (time_code == SECONDS)
		return (tv.tv_sec + (tv.tv_usec / 1000000L));
	else if (time_code == MILLISECONDS)
		return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
	else if (time_code == MICROSECONDS)
		return ((tv.tv_sec * 1000000L) + tv.tv_usec);
	else
		error_exit("Wrong input to gettime.");
	return (-1);
}

void	precise_usleep(long usec, t_data *data)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = gettime(MICROSECONDS);
	while (gettime(MICROSECONDS) - start < usec)
	{
		if (end(data))
			break ;
		elapsed = gettime(MICROSECONDS) - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
		{
			while (gettime(MICROSECONDS) - start < usec)
				;
		}
	}
}

void	error_exit(const char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}
