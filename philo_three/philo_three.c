/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:17:06 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/24 19:44:03 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	free_all(t_observer *observer, sem_t *sem, int error)
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
		if (g_sem_view)
		{
			sem_unlink("/sem_view");
			sem_close(sem);
		}
	}
	return (print_error(error));
}

int			main(int argc, char **argv)
{
	sem_t		*sem;
	t_observer	*observer;
	int			ret;

	observer = NULL;
	sem = NULL;
	if ((ret = init_observer(&observer, argc, argv)))
		return (free_all(observer, sem, ret));
	if ((ret = init_sem(&sem, observer->number_philo)))
		return (free_all(observer, sem, ret));
	if ((ret = init_processes(observer, sem)))
		return (free_all(observer, sem, ret));
	return (0);
}
