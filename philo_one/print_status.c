/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 17:36:12 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/18 13:53:53 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		print_error(int error)
{
	if (error == WRONG_ARGS)
		ft_putstr_fd("Error: wrong arguments\n", 2);
	else if (error == MALLOC_ERROR)
		ft_putstr_fd("Error: malloc error\n", 2);
	return (error);
}

void	view_status(t_philo *philo, int action)
{
	struct timeval	time;
	size_t			val_time;

	if (g_died && action != DIED && action != EAT_END)
		return ;
	gettimeofday(&time, NULL);
	val_time = (size_t)(time.tv_sec * 1000
		+ time.tv_usec / 1000 - philo->start_sim);
	if (action == TOOK_FORK_LEFT)
		init_string(val_time, philo->number, "has taken left fork\n");
	else if (action == TOOK_FORK_RIGHT)
		init_string(val_time, philo->number, "has taken right fork\n");
	else if (action == SLEEPING)
		init_string(val_time, philo->number, "is sleeping\n");
	else if (action == EATING)
		init_string(val_time, philo->number, "is eating\n");
	else if (action == THINKING)
		init_string(val_time, philo->number, "is thinking\n");
	else if (action == DIED)
		init_string(val_time, philo->number, "died\n");
	else if (action == EAT_END)
		init_string(val_time, philo->number, "numbs_to_eat ended\n");
}
