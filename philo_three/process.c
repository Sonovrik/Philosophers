/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:33:39 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/24 20:07:24 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int		check_death_thread(t_observer *obsever,
							size_t time_to_die)
{
	size_t			val_time;
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	val_time = (size_t)((time.tv_sec -
		obsever->last_meal.tv_sec) * 1000 + ((time.tv_usec -
		obsever->last_meal.tv_usec) / 1000));
	if (val_time == 1000)
		return (0);
	if (((time.tv_sec - obsever->last_meal.tv_sec) > 0
		|| ((time.tv_sec - obsever->last_meal.tv_sec) >= 0
		&& (time.tv_usec - obsever->last_meal.tv_usec) >= 0))
		&& val_time > time_to_die)
	{
		if (obsever->numbs_to_eat != 0)
			view_status(obsever, obsever->number, DIED);
		else
			view_status(obsever, obsever->number, EAT_END);
		return (-1);
	}
	return (0);
}

static void		kill_processes(t_observer *observer)
{
	int				i;

	i = 0;
	while (i < observer->number_philo)
	{
		kill(observer->pid[i], SIGKILL);
		i++;
	}
	exit(0);
}

void			*check_process(void *var)
{
	t_observer	*observer;

	observer = (t_observer *)var;
	while (1)
	{
		usleep(10);
		if (check_death_thread(observer,
			observer->time_to_die))
			exit(1);
	}
	return (NULL);
}

int				philo_live(t_observer *observer, sem_t *sem)
{
	pthread_create(&observer->thread, NULL, &check_process, observer);
	while (1)
	{
		sem_wait(sem);
		view_status(observer, observer->number, TOOK_FORK_LEFT);
		sem_wait(sem);
		view_status(observer, observer->number, TOOK_FORK_RIGHT);
		if (gettimeofday(&observer->last_meal, NULL))
			return (-1);
		view_status(observer, observer->number, EATING);
		my_usleep(observer->time_to_eat);
		sem_post(sem);
		sem_post(sem);
		observer->numbs_to_eat--;
		view_status(observer, observer->number, SLEEPING);
		my_usleep(observer->time_to_sleep);
		if (observer->numbs_to_eat == 0)
			exit(2);
		view_status(observer, observer->number, THINKING);
	}
	return (0);
}

int				wait_exit(t_observer *observer)
{
	int				status;
	int				ret;
	int				j;

	j = 0;
	while (1)
	{
		waitpid(-1, &status, 0);
		ret = WEXITSTATUS(status);
		if (ret == 2)
			j++;
		else
			kill_processes(observer);
		if (j == observer->number_philo)
		{
			ft_putstr_fd("All the philosophers have eaten\n", 1);
			kill_processes(observer);
		}
	}
	exit(1);
}
