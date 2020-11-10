/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 17:36:12 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/10 19:50:39 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex00.h"

int			print_error(int error)
{
	if (error == WRONG_ARGS)
		ft_putstr_fd("Error: wrong arguments\n", 2);
	else if (error == MALLOC_ERROR)
		ft_putstr_fd("Error: malloc error\n", 2);
	return (error);
}

void	view_status(int philo, int action)
{
	ft_putstr_fd("timestamp_in_ms ", 1);
	ft_putnbr_fd(philo, 1);
	if (action == TOOK_FORK)
		ft_putstr_fd(" has taken a fork\n", 1);
	else if (action == SLEEPING)
		ft_putstr_fd(" is sleeping\n", 1);
	else if (action == EATING)
		ft_putstr_fd(" is eating\n", 1);
	else if (action == THINKING)
		ft_putstr_fd(" is thinking\n", 1);
	else if (action == DIED)
		ft_putstr_fd(" died\n", 1);

}