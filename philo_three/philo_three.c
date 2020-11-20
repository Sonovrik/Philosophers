/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:17:06 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/20 22:58:37 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	free_all(t_observer *observer, sem_t *sem, int error) // ???
{
	if (observer)
	{
		if (observer->pid)
			free(observer->pid);
		free(observer);
	}
	if (sem)
	{
		sem_unlink("/sem");
		sem_close(sem);
	}
	return (print_error(error));
}

static int	init_observer(t_observer **observer, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (WRONG_ARGS);
	if ((*observer = (t_observer *)malloc(sizeof(t_observer))) == NULL)
		return (MALLOC_ERROR);
	if (init_args(observer, argv, argc))
		return (WRONG_ARGS);
	if (((*observer)->pid = (pid_t *)malloc(sizeof(pid_t) * (*observer)->number_philo)) == NULL)
		return (MALLOC_ERROR);
	return (0);
}

static int	init_sem(sem_t **sem, int len)
{
	sem_unlink("/sem");
	if ((*sem = sem_open("/sem", O_CREAT, S_IRWXU, len)) == NULL)
		return (MALLOC_ERROR);
	return (0);
}

static int		check_death_thread(struct timeval time, t_observer *obsever,
							size_t time_to_die)
{
	size_t		val_time;

	val_time = (size_t)((time.tv_sec -
		obsever->last_meal.tv_sec) * 1000 + ((time.tv_usec -
		obsever->last_meal.tv_usec) / 1000));
	if (((time.tv_sec - obsever->last_meal.tv_sec) > 0
		|| ((time.tv_sec - obsever->last_meal.tv_sec) >= 0
		&& (time.tv_usec - obsever->last_meal.tv_usec) >= 0))
		&& val_time > time_to_die)
	{
		g_died = 1;
		if (obsever->numbs_to_eat != 0)
			view_status(obsever, obsever->number, DIED, val_time);
		else
			view_status(obsever, obsever->number, EAT_END, val_time);
		return (-1);
	}
	return (0);
}

void		*check_process(void *var)
{
	t_observer		*observer;
	struct timeval	time;

	observer = (t_observer *)var;
	while (1)
	{
		if (gettimeofday(&time, NULL))
			continue;
		if (check_death_thread(time, observer,
			observer->time_to_die))
			exit(1);
	
	}
}

static int	philo_live(t_observer *observer, sem_t *sem)
{
	pthread_create(&observer->thread, NULL, &check_process, observer);
	while (1)
	{
		// if (observer->numbs_to_eat == 0)
		// 	exit(2);
		sem_wait(sem);
		view_status(observer, observer->number, TOOK_FORK_LEFT, 0);
		sem_wait(sem);
		view_status(observer, observer->number, TOOK_FORK_RIGHT, 0);
		if (gettimeofday(&observer->last_meal, NULL))
			return (-1);
		view_status(observer, observer->number, EATING, 0);
		my_usleep(observer->time_to_eat);
		sem_post(sem);
		sem_post(sem);
		observer->numbs_to_eat--;
		view_status(observer, observer->number, SLEEPING, 0);
		// usleep(1000 * observer->time_to_sleep);
		my_usleep(observer->time_to_sleep);
		if (observer->numbs_to_eat == 0)
			exit(2);
		view_status(observer, observer->number, THINKING, 0);
	}
	return (0);
}

static int	start_process(t_observer *observer, sem_t *sem)
{
	if (gettimeofday(&(observer->last_meal), NULL))
		return (-1);
	observer->start_sim = (size_t)observer->last_meal.tv_sec * 1000 + (size_t)observer->last_meal.tv_usec / 1000;
	philo_live(observer, sem);
	exit(1);

}

static int	init_processes(t_observer *observer, sem_t *sem)
{
	int		i;
	int		status;
	int		j;
	sem_t	*sem2;

	sem_unlink("/sem2");
	// sem2 = (sem_t *)malloc(sizeof(sem_t));
	sem2 = sem_open("/sem", O_CREAT, S_IRWXU, 0);
	j = 0;
	i = 0;
	while (i < observer->number_philo)
	{
		observer->pid[i] = fork();
		if (observer->pid[i] < 0)
			return (MALLOC_ERROR);
		if (observer->pid[i] == 0)
		{
			sem_wait(sem2);
			observer->number = i + 1;
			if (start_process(observer, sem))
				return (MALLOC_ERROR);
		}
		i++;
	}
	i = -1;
	while (++i < observer->number_philo)
		sem_post(sem2);
	while (1)
	{
		waitpid(-1, &status, 0);
		int ret = WEXITSTATUS(status);
		if (ret == 2)
			j++;
		else
		{
			i = 0;
			while (i < observer->number_philo)
			{
				kill(observer->pid[i], SIGKILL);
				i++;
			}
			exit(0);
		}
		if (j == observer->number_philo)
		{
			i = 0;
			while (i < observer->number_philo)
			{
				kill(observer->pid[i], SIGKILL);
				i++;
			}
			ft_putstr_fd("All the philosophers have eaten\n", 1);
			exit(0);
		}

		
	}
	exit (1);
}

int			main(int argc, char **argv)
{
	sem_t		*sem;
	t_observer	*observer;
	int			ret;

	g_died = 0;
	observer = NULL;
	sem = NULL;
	sem_unlink("/sem3");
	sem3 = sem_open("/sem3", O_CREAT, S_IRWXU, 1);
	if ((ret = init_observer(&observer, argc, argv)))
		return (free_all(observer, sem, ret));
	if ((ret = init_sem(&sem, observer->number_philo)))
		return (free_all(observer, sem, ret));
	sem_unlink("/sem2");
	observer->sem2 = sem_open("/sem2", O_CREAT, S_IRWXU, 1);
	if ((ret = init_processes(observer, sem)))
		return (free_all(observer, sem, ret));
	return (0);
}
