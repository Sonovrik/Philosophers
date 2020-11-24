/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 17:36:12 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/24 20:06:52 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		print_error(int error)
{
	if (error == WRONG_ARGS)
		ft_putstr_fd("Error: wrong arguments\n", 2);
	else if (error == MALLOC_ERROR)
		ft_putstr_fd("Error: malloc error\n", 2);
	return (error);
}

void	view_status(t_observer *observer, int number, int action)
{
	struct timeval	time;
	size_t			val_time;

	sem_wait(g_sem_view);
	if (gettimeofday(&time, NULL))
		return ;
	val_time = (size_t)(time.tv_sec * 1000
		+ time.tv_usec / 1000 - observer->start_sim);
	if (action == TOOK_FORK_LEFT)
		init_string(val_time, number, "has taken left fork\n");
	else if (action == TOOK_FORK_RIGHT)
		init_string(val_time, number, "has taken right fork\n");
	else if (action == SLEEPING)
		init_string(val_time, number, "is sleeping\n");
	else if (action == EATING)
		init_string(val_time, number, "is eating\n");
	else if (action == THINKING)
		init_string(val_time, number, "is thinking\n");
	else if (action == DIED)
		init_string(val_time, number, "died\n");
	else if (action == EAT_END)
		ft_putstr_fd("All the philosophers have eaten\n", 1);
	if (action != DIED)
		sem_post(g_sem_view);
}
