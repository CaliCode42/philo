/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:50:10 by tcali             #+#    #+#             */
/*   Updated: 2025/04/29 11:04:58 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/libft.h"
typedef struct	s_philo_data
{
	int	nb_philo;
	int	death;
	int	eat;
	int	sleep;
	int	meals;
}		t_philo_data;

#endif