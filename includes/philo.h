/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:50:10 by tcali             #+#    #+#             */
/*   Updated: 2025/05/20 17:29:25 by tcali            ###   ########.fr       */
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
	int				death;
	int				eat;
	int				sleep;
	int				meals;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	mutex_rip;
	int				start_time;
	int				rip;
}		t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread_id;
	t_data			*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_philo	*prev;
	struct s_philo	*next;
}		t_philo;

//parse_args.c
int		init_data(t_data *data, char **args);

//create_philo.c
t_philo	*philo_new(int id, t_data *data);
void	philo_add_back(t_philo **philo, t_philo *new);
t_philo	*create_new_philo(t_philo **philo, int id, t_data *data);
void	init_philosophers(int total, t_philo **philo, t_data *data);

//threads.c
void	start_threads(t_data *data, t_philo *philo);
void	join_threads(t_data *data, t_philo *philo);

//main.c
long	get_time_ms(void);
void	*philo_routine(void *arg);

//debug.c
void	print_philos(t_philo *philo, int total);

//check
int		should_stop(t_philo *philo);
int		check_philos(t_philo *philo, t_data *data);

#endif