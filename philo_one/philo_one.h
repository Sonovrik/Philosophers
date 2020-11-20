/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 12:45:32 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/20 13:17:14 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <string.h>

# define WRONG_ARGS -2
# define MALLOC_ERROR 12
# define SLEEPING 1001
# define EATING 1002
# define THINKING 1003
# define DIED 1004
# define TOOK_FORK_LEFT 1005
# define TOOK_FORK_RIGHT 1006
# define EAT_END 1007

int					g_died;
int					g_count_die;

typedef struct		s_philo
{
	int				number;
	size_t			numbs_to_eat;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	struct timeval	live_time;
	size_t			start_sim;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_t		thread;
}					t_philo;

typedef struct		s_observer
{
	t_philo			*philo;
	int				number_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			numbs_to_eat;
	pthread_t		thread;
}					t_observer;

int					ft_strlen(char *str);
void				ft_putstr_fd(char *str, int fd);
int					ft_atoi(char *str, size_t *nbr);
void				ft_putchar_fd(char c, int fd);

int					print_error(int error);
void				view_status(t_philo *philo, int action, size_t val_time2);
void				my_usleep(size_t time);

void				init_string(size_t val_time, size_t number, char *text);
int					init_args(t_observer **observer, char **argv, int argc);
int					init_mutex(pthread_mutex_t **mutex, int len);
int					init_philo(t_philo **philo, pthread_mutex_t *mutex,
						t_observer *observer);

int					start_philo(t_philo *philo, int len);
int					observer_start(t_observer *observer, t_philo *philo);

#endif
