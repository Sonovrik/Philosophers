/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:17:06 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/18 21:56:41 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	free_all(t_observer *observer, sem_t *sem, int error)
{
	int				i;

	if (observer && observer->philo != NULL)
	{
		i = -1;
		while (i < observer->number_philo && observer->philo[++i].thread)
			pthread_detach(observer->philo[i].thread);
		free(observer->philo);
		observer->philo = NULL;
	}
	if (sem)
	{
		sem_unlink("/sem");
		sem_close(sem);
		sem = NULL;
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

static int	init_all_threads(t_observer *observer, sem_t *sem,
					t_philo **philo)
{
	if (init_sem(&sem, observer->number_philo))
		return (MALLOC_ERROR);
	if (init_philo(philo, sem, observer))
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
	t_philo		*philo;
	sem_t		*sem;
	t_observer	*observer;
	int			ret;

	philo = NULL;
	observer = NULL;
	sem = NULL;
	g_died = 0;
	if ((ret = init_observer(&observer, argc, argv)))
		return (free_all(observer, sem, ret));
	if ((ret = init_all_threads(observer, sem, &philo)))
		return (free_all(observer, sem, ret));
	if ((ret = start_threads(observer, philo)))
		return (free_all(observer, sem, ret));
	while (1)
	{
		if (g_died)
		{
			free_all(observer, sem, 0);
			return (1);
		}
	}
	return (0);
}
