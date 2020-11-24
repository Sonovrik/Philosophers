/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 12:55:26 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/24 13:55:48 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	free_all(t_observer *observer, pthread_mutex_t **mutex, int error)
{
	int				i;

	if (observer && observer->philo != NULL)
	{
		usleep(10);
		free(observer->philo);
		observer->philo = NULL;
	}
	if (*mutex)
	{
		i = -1;
		while (++i < observer->number_philo)
			pthread_mutex_destroy(&(*mutex)[i]);
		free(*mutex);
		*mutex = NULL;
	}
	if (observer)
	{
		free(observer);
		observer = NULL;
	}
	return (print_error(error));
}

static int	init_observer(t_observer **observer, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (WRONG_ARGS);
	if ((*observer = (t_observer *)malloc(sizeof(t_observer))) == NULL)
		return (MALLOC_ERROR);
	(*observer)->philo = NULL;
	if (init_args(observer, argv, argc))
		return (WRONG_ARGS);
	return (0);
}

static int	init_all_threads(t_observer *observer, pthread_mutex_t **mutex,
					t_philo **philo)
{
	if (init_mutex(mutex, observer->number_philo))
		return (MALLOC_ERROR);
	if (init_philo(philo, *mutex, observer))
		return (MALLOC_ERROR);
	return (0);
}

static int	start_threads(t_observer *observer, t_philo *philo)
{
	if (start_philo(philo, observer->number_philo))
		return (MALLOC_ERROR);
	if (observer_start(observer, philo))
		return (MALLOC_ERROR);
	return (0);
}

int			main(int argc, char **argv)
{
	t_philo			*philo;
	pthread_mutex_t	*mutex;
	t_observer		*observer;
	int				ret;

	mutex = NULL;
	observer = NULL;
	philo = NULL;
	g_died = 0;
	g_count_die = 0;
	if ((ret = init_observer(&observer, argc, argv)))
		return (free_all(observer, &mutex, ret));
	if ((ret = init_all_threads(observer, &mutex, &philo)))
		return (free_all(observer, &mutex, ret));
	if ((ret = start_threads(observer, philo)))
		return (free_all(observer, &mutex, ret));
	while (1)
	{
		if (g_died)
		{
			free_all(observer, &mutex, 0);
			return (1);
		}
	}
	return (0);
}
