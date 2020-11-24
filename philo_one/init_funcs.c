/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:03:22 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/24 19:42:57 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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

int		init_mutex(pthread_mutex_t **mutex, int len)
{
	int					i;

	i = 0;
	if ((*mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * len))
		== NULL)
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

int		init_philo(t_philo **philo, pthread_mutex_t *mutex,
						t_observer *observer)
{
	int					i;

	i = 0;
	if ((*philo = (t_philo *)malloc(sizeof(t_philo)
		* observer->number_philo)) == NULL)
		return (-1);
	while (i < observer->number_philo)
	{
		(*philo)[i].numbs_to_eat = observer->numbs_to_eat;
		(*philo)[i].number = i + 1;
		(*philo)[i].left = &(mutex[i]);
		(*philo)[i].right = &(mutex[(i + 1) % observer->number_philo]);
		(*philo)[i].thread = NULL;
		(*philo)[i].time_to_eat = observer->time_to_eat;
		(*philo)[i].time_to_sleep = observer->time_to_sleep;
		i++;
	}
	return (0);
}
