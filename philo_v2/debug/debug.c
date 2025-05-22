/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:56:06 by tcali             #+#    #+#             */
/*   Updated: 2025/05/20 17:07:05 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philos(t_philo *philo, int total)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	tmp = philo;
	while (i < total)
	{
		ft_printf("Philo %d - Left Fork: %p | Right Fork: %p | Next: %d\n",
			tmp->id,
			(void *)tmp->left_fork,
			(void *)tmp->right_fork,
			tmp->next->id);
		tmp = tmp->next;
		i++;
	}
}
