/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex00.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:16:56 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/12 18:34:04 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef EX00_H
# define EX00_H

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
# define TOOK_FORK 1005

typedef struct		s_args
{
	size_t			number_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				numbs_to_eat;
}					t_args;

typedef struct		s_philo
{
	size_t			number;
	int				number_eat;
	long			start_time;
	struct timeval	*last_meal;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_t		thread;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
}					t_philo;

typedef struct		s_looker
{
	t_philo			*philo;
	size_t			number_philo;
}					t_looker;


int		ft_strlen(char *str);
void	ft_putstr_fd(char *str, int fd);
int		ft_atoi(char *str, size_t *nbr);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
int		print_error(int error);
void	view_status(int philo, int action);


#endif