/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:33:39 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/17 22:11:05 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		my_usleep(size_t time)
{
	struct timeval	stamp;
	size_t			start;
	size_t			now;

	gettimeofday(&stamp, NULL);
	start = stamp.tv_sec * 1000 + stamp.tv_usec / 1000;
	now = start;
	while (now - start < time)
	{
		usleep(100);
		gettimeofday(&stamp, NULL);
		now = stamp.tv_sec * 1000 + stamp.tv_usec / 1000;
	}
	return ;
}

void		*philo_live(void *var)
{
	t_philo			*philo;

	philo = (t_philo *)var;
	while (1)
	{
		if (philo->numbs_to_eat != 0)
		{
			pthread_mutex_lock(philo->left);
			view_status(philo, TOOK_FORK_LEFT);
			pthread_mutex_lock(philo->right);
			view_status(philo, TOOK_FORK_RIGHT);
			gettimeofday(&philo->live_time, NULL);
			view_status(philo, EATING);
			my_usleep(philo->time_to_eat);
			pthread_mutex_unlock(philo->right);
			pthread_mutex_unlock(philo->left);
			philo->numbs_to_eat--;
			view_status(philo, SLEEPING);
			my_usleep(philo->time_to_sleep);
			view_status(philo, THINKING);
		}
	}
}

void		check_death_thread(struct timeval time, t_philo *philo,
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
	}
	return ;
}

void		*checking_threads(void *var)
{
	int				i;
	t_observer		*observer;
	struct timeval	time;
	size_t			val_time;

	observer = (t_observer *)var;
	while (1)
	{
		i = 0;
		while (i < observer->number_philo)
		{
			gettimeofday(&time, NULL);
			val_time = (size_t)((time.tv_sec -
				observer->philo[i].live_time.tv_sec) * 1000 + ((time.tv_usec -
				observer->philo[i].live_time.tv_usec) / 1000));
			check_death_thread(time, &observer->philo[i],
				val_time, observer->time_to_die);
			i++;
		}
	}
	return (NULL);
}

int			start_philo(t_philo *philo, int len)
{
	int				i;

	i = 0;
	while (i < len)
	{
		usleep(100);
		gettimeofday(&philo[i].live_time, NULL);
		philo[i].start_sim = philo[i].live_time.tv_sec * 1000
			+ philo[i].live_time.tv_usec / 1000;
		if (pthread_create(&(philo[i].thread), NULL, &philo_live, &(philo[i])))
			return (-1);
		i++;
	}
	return (0);
}

int			observer_start(t_observer *observer, t_philo *philo)
{
	observer->philo = philo;
	if (pthread_create(&(observer->thread), NULL, &checking_threads, observer))
		return (-1);
	return (0);
}
