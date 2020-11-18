/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:33:39 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/18 17:56:09 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void		*philo_live(void *var)
{
	t_philo			*philo;

	philo = (t_philo *)var;
	while (1)
	{
		if (philo->numbs_to_eat == 0 || g_died)
			return (NULL);
		sem_wait(philo->sem);
		view_status(philo, TOOK_FORK_LEFT);
		sem_wait(philo->sem);
		view_status(philo, TOOK_FORK_RIGHT);
		if (gettimeofday(&philo->live_time, NULL))
		{
			g_died = 1;
			return (NULL);
		}
		view_status(philo, EATING);
		my_usleep(philo->time_to_eat);
		sem_post(philo->sem);
		sem_post(philo->sem);
		philo->numbs_to_eat--;
		view_status(philo, SLEEPING);
		my_usleep(philo->time_to_sleep);
		view_status(philo, THINKING);
	}
}

static int		check_death_thread(struct timeval time, t_philo *philo,
							size_t val_time, size_t time_to_die)
{
	if (time.tv_sec - philo->live_time.tv_sec > 0
		&& val_time > time_to_die)
	{
		g_died = 1;
		if (philo->numbs_to_eat != 0)
			view_status(philo, DIED);
		else
			view_status(philo, EAT_END);
		return (-1);
	}
	return (0);
}

static void		*checking_threads(void *var)
{
	int				i;
	t_observer		*observer;
	struct timeval	time;
	size_t			val_time;

	observer = (t_observer *)var;
	while (1)
	{
		i = -1;
		while (++i < observer->number_philo)
		{
			if (gettimeofday(&time, NULL))
			{
				g_died = 1;
				return (NULL);
			}
			val_time = (size_t)((time.tv_sec -
				observer->philo[i].live_time.tv_sec) * 1000 + ((time.tv_usec -
				observer->philo[i].live_time.tv_usec) / 1000));
			if (check_death_thread(time, &observer->philo[i],
				val_time, observer->time_to_die))
				return (NULL);
		}
	}
	return (NULL);
}

int				start_philo(t_philo *philo, int len)
{
	int				i;

	i = 0;
	while (i < len)
	{
		usleep(100);
		if (gettimeofday(&philo[i].live_time, NULL))
			return (-1);
		philo[i].start_sim = philo[i].live_time.tv_sec * 1000
			+ philo[i].live_time.tv_usec / 1000;
		if (pthread_create(&(philo[i].thread), NULL, &philo_live, &(philo[i])))
			return (-1);
		i++;
	}
	return (0);
}

int				observer_start(t_observer *observer, t_philo *philo)
{
	observer->philo = philo;
	if (pthread_create(&(observer->thread), NULL, &checking_threads, observer))
		return (-1);
	return (0);
}
