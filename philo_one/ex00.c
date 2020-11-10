/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex00.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:40:38 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/10 21:38:36 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex00.h"


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
		new[i].number_eat = all->numbs_to_eat;
		new[i].last_meal = NULL;
		new[i].left = &mutex[i];
		new[i].right = &mutex[(i + 1) % all->number_philo];
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

void		*eating(void	*mutex)
{
	pthread_mutex_t *tmp;

	tmp = (pthread_mutex_t *)mutex;
	// pthread_mutex_lock(&tmp[0]);
	// pthread_mutex_lock(&tmp[1]);
	view_status(1, EATING);
	usleep(1000000);
	// pthread_mutex_unlock(&tmp[0]);
	// pthread_mutex_unlock(&tmp[1]);
	return (NULL);
}

int			philo_start(t_philo *philo, pthread_mutex_t *mutex)
{
	pthread_create(&philo[0].thread, NULL, &eating, mutex);
	// view_status(1, EATING);
	return (1);
}

int main(int argc, char **argv)
{
	t_args all;
	// struct timeval time1, time2;
	// struct timeval tz;

	t_philo *philo;
	pthread_mutex_t *mutex;

	if (argc < 5 || argc > 6)
		return (print_error(WRONG_ARGS));
	if (init_args(&all, argv, argc))
		return (print_error(WRONG_ARGS));
	if ((mutex = init_mutexs(all.number_philo)) == NULL)
		return(print_error(MALLOC_ERROR));
	if ((philo = init_philos(&all, mutex)) == NULL)
		return(print_error(MALLOC_ERROR));
	philo_start(philo, mutex);
	pthread_join(philo[0].thread, NULL);

}