/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:35:26 by tcali             #+#    #+#             */
/*   Updated: 2025/05/22 17:40:48 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/libft.h"

typedef struct s_data
{
	int				nb_philo;
	int				t_death;
	int				t_eat;
	int				t_sleep;
	int				nb_meals;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	m_rip;
	int				start_time;
	int				rip;
	struct s_philo	*philo;
}		t_data;

typedef struct s_philo
{
	int				id;
	int				meals;
	long			last_meal;
	pthread_t		thread_id;
	pthread_mutex_t	thread_meals;
	pthread_mutex_t	thread_last_meal;
	t_data			*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_philo	*prev;
	struct s_philo	*next;
}		t_philo;

#endif