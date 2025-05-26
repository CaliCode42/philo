/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:35:26 by tcali             #+#    #+#             */
/*   Updated: 2025/05/26 19:35:06 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>
# include <stdlib.h>
# include <errno.h>
# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

typedef pthread_mutex_t	t_mtx;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef enum e_time_code
{
	SECONDS,
	MILLISECONDS,
	MICROSECONDS,
}	t_time_code;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_CHOPSTICK_ONE,
	TAKE_CHOPSTICK_TWO,
	DIED,
}	t_status;

typedef struct s_chopstick
{
	t_mtx	chopstick;
	int		chopstick_id;
}			t_chopstick;

typedef struct s_data
{
	long			nb_philo;
	long			t_death;
	long			t_eat;
	long			t_sleep;
	long			nb_meals;
	t_mtx			m_print;
	t_mtx			m_eat;
	t_mtx			m_stop;
	t_mtx			m_data;
	long			start_time;
	bool			quit;
	bool			threads_ready;
	long			threads_running_nb;
	pthread_t		monitor;
	t_chopstick		*chopsticks;
	struct s_philo	*philos;
}		t_data;

typedef struct s_philo
{
	int				id;
	long			meals;
	long			t_last_meal;
	bool			full;
	pthread_t		thread_id;
	t_mtx			mutex_meals;
	t_mtx			mutex_last_meal;
	t_mtx			m_philo;
	t_data			*data;
	t_chopstick		*chopstick_one;
	t_chopstick		*chopstick_two;
	struct s_philo	*prev;
	struct s_philo	*next;
}		t_philo;

//parse.c
void	parse_input(t_data *data, char **av);

//utils.c
void	error_exit(const char *error);
long	gettime(t_time_code time_code);
void	precise_usleep(long usec, t_data *data);

//safe.c
void	*safe_malloc(size_t bytes);
void	*safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*f)(void *),
			void *data, t_opcode opcode);

//init.c
void	init_data(t_data *data, char **av);

//getters_setters.c
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
bool	end(t_data *data);
void	set_long(t_mtx *mutex, long *dest, long value);
long	get_long(t_mtx *mutex, long *value);

//sync_utils.c
void	wait_all_threads(t_data *data);
void	increase_long(t_mtx *mutex, long *value);
bool	all_threads_running(t_mtx *mutex, long *threads,
			long philo_nb);

//routine.c
void	start_threads(t_data *data);

//monitor.c
void	*monitor_routine(void *arg);

//write.c
void	write_status(t_status status, t_philo *philo, bool debug);

#endif