/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:52:31 by tcali             #+#    #+#             */
/*   Updated: 2025/05/26 17:45:59 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	write_status_debug(t_status status, t_philo *philo, long elapsed)
{
	if (status == TAKE_CHOPSTICK_ONE && !end(philo->data))
		printf("%ld : %d has taken 1° chopstick\nfork = %d\n",
			elapsed, philo->id, philo->chopstick_one->chopstick_id);
	else if (status == TAKE_CHOPSTICK_TWO && !end(philo->data))
		printf("%ld : %d has taken 2° chopstick\nfork = %d\n",
			elapsed, philo->id, philo->chopstick_two->chopstick_id);
	else if (status == EATING && !end(philo->data))
		printf("%ld : %d is eating\nnb of meals = %ld\n",
			elapsed, philo->id, philo->meals);
	else if (status == SLEEPING && !end(philo->data))
		printf("%ld : %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING && !end(philo->data))
		printf("%ld : %d is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf("%ld : %d died\n", elapsed, philo->id);
}

void	write_status(t_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = gettime(MILLISECONDS);
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->data->m_print, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((status == TAKE_CHOPSTICK_ONE || status == TAKE_CHOPSTICK_TWO)
			&& !end(philo->data))
			printf("%ld : %d has taken a chopstick\n", elapsed, philo->id);
		else if (status == EATING && !end(philo->data))
			printf("%ld : %d is eating\n", elapsed, philo->id);
		else if (status == SLEEPING && !end(philo->data))
			printf("%ld : %d is sleeping\n", elapsed, philo->id);
		else if (status == THINKING && !end(philo->data))
			printf("%ld : %d is thinking\n", elapsed, philo->id);
		else if (status == DIED)
			printf("%ld : %d died\n", elapsed, philo->id);
	}
	safe_mutex_handle(&philo->data->m_print, UNLOCK);
}
