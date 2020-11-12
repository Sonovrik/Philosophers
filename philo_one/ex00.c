/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex00.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:40:38 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/12 20:12:03 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex00.h"

int		died;

int			init_args(t_args *all, char **args, int argc)
{
	if (ft_atoi(args[1], &(all->number_philo)) || all->number_philo < 2)
		return (-1);
	if (ft_atoi(args[2], &(all->time_to_die)))
		return (-1);
	if (ft_atoi(args[3], &(all->time_to_eat)))
		return (-1);
	if (ft_atoi(args[4], &(all->time_to_sleep)))
		return (-1);
	if (argc == 5)
		all->numbs_to_eat = -1;
	else if (ft_atoi(args[5], (size_t *)&all->numbs_to_eat))
		return (-1);
	return (0);
}

t_philo		*init_philos(t_args *all, pthread_mutex_t *mutex)
{
	t_philo *new;
	int		i;

	i = 0;
	if ((new = (t_philo *)malloc(sizeof(t_philo) * (all->number_philo))) == NULL)
		return (NULL);
	while (i < (int)all->number_philo)
	{
		new[i].number = i + 1;
		new[i].last_meal = NULL;
		new[i].left = &mutex[i];
		new[i].right = &mutex[(i + 1) % all->number_philo];
		new[i].number_eat = all->numbs_to_eat;
		new[i].time_to_die = all->time_to_die;
		new[i].time_to_eat = all->time_to_eat;
		new[i].time_to_sleep = all->time_to_sleep;
		// new[i].thread = NULL; // ???
		i++;
	}
	return (new);
}

pthread_mutex_t		*init_mutexs(int count)
{
	pthread_mutex_t *new;

	if ((new = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (count))) == NULL)
		return (NULL);
	while (count != 0)
	{
		if (pthread_mutex_init(&(new[count]), NULL))
			return (NULL);
		count--;
	}
	return (new);
}

void		*start_eat(void	*philo)
{
	t_philo *tmp;

	tmp = (t_philo *)philo;
	while(1)
	{
		gettimeofday(tmp->last_meal, NULL);
		tmp->start_time = tmp->last_meal->tv_usec;
		pthread_mutex_lock(tmp->left);
		pthread_mutex_lock(tmp->right);
		view_status(tmp->number, EATING);
		usleep(1000000);
		pthread_mutex_unlock(tmp->left);
		pthread_mutex_unlock(tmp->right);
	}
	
	return (NULL);
}

void		kill_philo(t_looker *looker)
{
	
}

int			looker_view(void	*looker)
{
	t_looker	*tmp;
	int			i;

	i = 0;
	tmp = (t_looker *)looker;
	while (1)
	{
		i = 0;
		while (i < tmp->number_philo)
		{
			if (gettimeofday(tmp->philo[i].last_meal, NULL) - tmp->philo[i].start_time
				> tmp->philo->time_to_die)
			{
				died = 1;
			}
			i++;
		}
	}
}

int			philo_start(t_philo *philo, size_t number_philo)
{
	int		i;
	t_looker	*looker;

	i = 0;
	while (i < (int)number_philo)
	{
		pthread_create(&philo[i].thread, NULL, &start_eat, &philo[i]);
		i++;
	}
	looker = (t_looker *)malloc(sizeof(looker));
	looker->philo = philo;
	// view_status(1, EATING);
	while (1)
	{
		if (died)
		{
			// code to clear all and exit
		}
	}
	return (1);
}

int main(int argc, char **argv)
{
	t_args all;
	// struct timeval time1, time2;
	// struct timeval tz;

	t_philo *philo;
	pthread_mutex_t *mutex;

	died = 0;
	if (argc < 5 || argc > 6)
		return (print_error(WRONG_ARGS));
	if (init_args(&all, argv, argc))
		return (print_error(WRONG_ARGS));
	if ((mutex = init_mutexs(all.number_philo)) == NULL)
		return(print_error(MALLOC_ERROR));
	if ((philo = init_philos(&all, mutex)) == NULL)
		return(print_error(MALLOC_ERROR));
	philo_start(philo, all.number_philo);
	pthread_join(philo[0].thread, NULL);

}