/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:03:22 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/24 19:43:28 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		init_observer(t_observer **observer, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (WRONG_ARGS);
	if ((*observer = (t_observer *)malloc(sizeof(t_observer))) == NULL)
		return (MALLOC_ERROR);
	if (init_args(observer, argv, argc))
		return (WRONG_ARGS);
	if (((*observer)->pid = (pid_t *)malloc(sizeof(pid_t)
		* (*observer)->number_philo)) == NULL)
		return (MALLOC_ERROR);
	return (0);
}

int		init_sem(sem_t **sem, int len)
{
	sem_unlink("/sem");
	if ((*sem = sem_open("/sem", O_CREAT, S_IRWXU, len)) == NULL)
		return (MALLOC_ERROR);
	sem_unlink("/sem_view");
	if ((g_sem_view = sem_open("/sem_view", O_CREAT, S_IRWXU, 1)) == NULL)
		return (MALLOC_ERROR);
	return (0);
}

int		init_args(t_observer **observer, char **argv, int argc)
{
	if (ft_atoi(argv[1], (size_t *)&((*observer)->number_philo)))
		return (-1);
	if (ft_atoi(argv[2], (size_t *)&((*observer)->time_to_die)))
		return (-1);
	if (ft_atoi(argv[3], (size_t *)&((*observer)->time_to_eat)))
		return (-1);
	if (ft_atoi(argv[4], (size_t *)&((*observer)->time_to_sleep)))
		return (-1);
	if (argc == 5)
		(*observer)->numbs_to_eat = -1;
	else if (ft_atoi(argv[5], (size_t *)&((*observer)->numbs_to_eat)))
		return (-1);
	if ((*observer)->number_philo < 2 || (*observer)->time_to_die <= 0
		|| (*observer)->time_to_eat <= 0 || (*observer)->time_to_sleep <= 0
		|| (*observer)->numbs_to_eat < 1)
		return (-1);
	return (0);
}

int		init_processes(t_observer *observer, sem_t *sem)
{
	int		i;

	i = 0;
	if (gettimeofday(&(observer->last_meal), NULL))
		return (-1);
	observer->start_sim = (size_t)observer->last_meal.tv_sec
		* 1000 + (size_t)observer->last_meal.tv_usec / 1000;
	while (i < observer->number_philo)
	{
		observer->pid[i] = fork();
		if (observer->pid[i] < 0)
			return (MALLOC_ERROR);
		if (observer->pid[i] == 0)
		{
			observer->number = i + 1;
			philo_live(observer, sem);
			exit(0);
		}
		i++;
	}
	wait_exit(observer);
	return (0);
}
