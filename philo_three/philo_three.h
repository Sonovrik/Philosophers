/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:33:51 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/24 20:07:02 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <string.h>
# include <signal.h>

# define WRONG_ARGS -2
# define MALLOC_ERROR 12
# define SLEEPING 1001
# define EATING 1002
# define THINKING 1003
# define DIED 1004
# define TOOK_FORK_LEFT 1005
# define TOOK_FORK_RIGHT 1006
# define EAT_END 1007

sem_t				*g_sem_view;

typedef struct		s_observer
{
	int				number_philo;
	int				number;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			numbs_to_eat;
	struct timeval	last_meal;
	pid_t			*pid;
	pthread_t		thread;
	size_t			start_sim;
}					t_observer;

int					ft_strlen(char *str);
void				ft_putstr_fd(char *str, int fd);
int					ft_atoi(char *str, size_t *nbr);
void				ft_putchar_fd(char c, int fd);

int					print_error(int error);
void				view_status(t_observer *observer, int number, int action);
void				my_usleep(size_t time);

void				init_string(size_t val_time, size_t number, char *text);
int					init_args(t_observer **observer, char **argv, int argc);
int					init_observer(t_observer **observer, int argc, char **argv);
int					init_sem(sem_t **sem, int len);
int					init_processes(t_observer *observer, sem_t *sem);

int					philo_live(t_observer *observer, sem_t *sem);
void				*check_process(void *var);
int					wait_exit(t_observer *observer);

#endif
