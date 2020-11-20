/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:03:22 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/19 19:21:49 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
	else if (ft_atoi(argv[5], (size_t *)&((*observer)->numbs_to_eat))
		|| (*observer)->numbs_to_eat < 1)
		return (-1);
	if ((*observer)->number_philo < 2)
		return (-1);
	return (0);
}
