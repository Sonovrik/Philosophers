/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 12:45:32 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/13 20:41:48 by lmidori          ###   ########.fr       */
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
# define PUT_FORK_LEFT 1007
# define PUT_FORK_RIGHT 1007


int					died;

typedef struct		s_args
{
	int				number_philo;
	int				time_to_die;
	int				time_to_eat;
	int 			time_to_sleep;
	int				numbs_to_eat;
}					t_args;

typedef struct		s_philo
{
	int				number;
	int				numbs_to_eat;
	size_t			last_meal;
	int				time_to_eat;
	int 			time_to_sleep;
	struct timeval	*live_time;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_t		thread;
}					t_philo;

typedef struct		s_observer
{
	t_philo			*philo;
	int				number_philo;
	int				time_to_die;
	int				time_to_eat;
	int 			time_to_sleep;
	int				numbs_to_eat;
	pthread_t		thread;
}					t_observer;


int		ft_strlen(char *str);
void	ft_putstr_fd(char *str, int fd);
int		ft_atoi(char *str, int *nbr);
void	ft_putchar_fd(char c, int fd);
char	*ft_putnbr_fd(size_t n);
int		print_error(int error);
void	view_status(t_philo *philo, int action);

#endif