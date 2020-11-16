/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 12:55:26 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/16 21:39:49 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		my_usleep(size_t time)
{
	struct timeval stamp;
	size_t start;
	size_t now;
	
	gettimeofday(&stamp, NULL);
	start = stamp.tv_sec * 1000 + stamp.tv_usec / 1000;
	now = start;
	while (now - start < time / 1000)
	{
		usleep(100);
		gettimeofday(&stamp, NULL);
		now = stamp.tv_sec * 1000 + stamp.tv_usec / 1000;
	}
	return ;
}

int		init_args(t_observer **observer, char **argv, int argc)
{
	if ((*observer = (t_observer *)malloc(sizeof(t_observer))) == NULL)
		return (-1);
	if (ft_atoi(argv[1], &((*observer)->number_philo)))
		return (-1);
	if (ft_atoi(argv[2], &((*observer)->time_to_die)))
		return (-1);
	if (ft_atoi(argv[3], &((*observer)->time_to_eat)))
		return (-1);
	if (ft_atoi(argv[4], &((*observer)->time_to_sleep)))
		return (-1);
	if (argc == 5)
		(*observer)->numbs_to_eat = -1;
	else if (ft_atoi(argv[5], &((*observer)->numbs_to_eat)) || (*observer)->numbs_to_eat < 1)
		return (-1);
	if (argc != 5 && (*observer)->number_philo < 2)
		return (-1);
	return (0);
}

int		init_mutex(pthread_mutex_t **mutex, int len)
{
	int					i;

	i = 0;
	if ((*mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * len)) == NULL)
		return (-1);
	while (i < len)
	{
		if (pthread_mutex_init(&((*mutex)[i]), NULL))
		{
			while (--i > -1)
			{
				pthread_mutex_destroy(&((*mutex)[i]));
			}
			free(*mutex);
			*mutex = NULL;
			return (-1);
		}
		i++;
	}
	return (0);
}

int			init_philo(t_philo **philo, pthread_mutex_t *mutex, t_observer *observer)
{
	int					i;

	i = 0;
	if ((*philo = (t_philo *)malloc(sizeof(t_philo) * observer->number_philo)) == NULL)
		return (-1);
	while (i < observer->number_philo)
	{
		(*philo)[i].numbs_to_eat = observer->numbs_to_eat;
		(*philo)[i].number = i + 1;
		(*philo)[i].left = &(mutex[i]);
		(*philo)[i].right = &(mutex[(i + 1) % observer->number_philo]);
		(*philo)[i].last_meal = 0;
		(*philo)[i].live_time = (struct timeval *)malloc(sizeof(struct timeval));
		(*philo)[i].thread = NULL;
		(*philo)[i].time_to_eat = observer->time_to_eat;
		(*philo)[i].time_to_sleep = observer->time_to_sleep;
		i++;
	}
	return (0);
}

void		*philo_live(void *var)
{
	t_philo				*philo;
	
	philo = (t_philo *)var;
	while (1)
	{
		if (philo->numbs_to_eat != 0)
		{
			pthread_mutex_lock(philo->left);
			view_status(philo, TOOK_FORK_LEFT);
			pthread_mutex_lock(philo->right);
			view_status(philo, TOOK_FORK_RIGHT);
			gettimeofday(philo->live_time, NULL);
			philo->numbs_to_eat--;
			view_status(philo, EATING);
			my_usleep(philo->time_to_eat * 1000);
			pthread_mutex_unlock(philo->right);
			view_status(philo, PUT_FORK_RIGHT);
			pthread_mutex_unlock(philo->left);
			view_status(philo, PUT_FORK_LEFT);
			view_status(philo, SLEEPING);
			my_usleep(philo->time_to_sleep * 1000);
			view_status(philo, THINKING);
		}
	}
}

int			start_philo(t_philo *philo, int len)
{
	int					i;
	
	i = 0;
	while (i < len)
	{
		usleep(100);
		gettimeofday(philo[i].live_time, NULL);
		philo[i].start_sim = philo[i].live_time->tv_sec * 1000 + philo[i].live_time->tv_usec / 1000;
		if (pthread_create(&(philo[i].thread), NULL, &philo_live, &(philo[i])))
		{
			while (--i > -1)
				pthread_detach(philo[i].thread); // ???
			return (-1);
		}
		i++;
	}
	return (0);
}

void		*checking_threads(void *var)
{
	int					i;
	t_observer			*observer;
	struct				timeval time;
	size_t				val_time;
	// size_t				time;

	observer = (t_observer *)var;
	while (1)
	{
		i = 0;
		while (i < observer->number_philo)
		{
			gettimeofday(&time, NULL);
			usleep(50);
			val_time = (size_t)((time.tv_sec - observer->philo[i].live_time->tv_sec) * 1000
				+ ((time.tv_usec - observer->philo[i].live_time->tv_usec) / 1000));
			if (val_time > (size_t)observer->time_to_die)
			{
				died = 1;
				printf("HE IS DIE O MY GOD %d	%zu!!!\n", observer->philo[i].number, val_time);
				return (NULL); //???
			}
			i++;
		}
	}
	return (NULL);
}


int		observer_start(t_observer *observer, t_philo *philo)
{
	observer->philo = philo;
	if (pthread_create(&(observer->thread), NULL, &checking_threads, observer))
	{
		pthread_detach(observer->thread); // ?????????
		return (-1);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_philo				*philo;
	pthread_mutex_t		*mutex;
	t_observer			*observer;

	mutex = NULL;
	observer = NULL;
	philo = NULL;
	died = 0;
	if (argc < 5 || argc > 6)
		return (print_error(WRONG_ARGS));
	if (init_args(&observer, argv, argc))
	{
		free(observer);
		return (print_error(WRONG_ARGS));
	}
	if (init_mutex(&mutex, observer->number_philo))
	{
		free(observer);
		return(print_error(MALLOC_ERROR));
	}
	if (init_philo(&philo, mutex, observer))
	{
		free(observer);
		free(mutex);
		return(print_error(MALLOC_ERROR));
	}
	if (start_philo(philo, observer->number_philo))
	{
		free(observer);// ?????????
		free(mutex);
		return(print_error(MALLOC_ERROR));
	}
	if (observer_start(observer, philo))
	{
		free(observer);// ?????????
		free(mutex);
		return(print_error(MALLOC_ERROR));
	}
	while (1)
	{
		if (died)
			exit(1);
	}
	return (0);
}