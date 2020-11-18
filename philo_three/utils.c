/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:19:27 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/18 21:58:14 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void		my_usleep(size_t time)
{
	struct timeval	stamp;
	size_t			start;
	size_t			now;

	while (1)
	{
		if (gettimeofday(&stamp, NULL))
			continue ;
		start = stamp.tv_sec * 1000 + stamp.tv_usec / 1000;
		now = start;
		while (now - start < time)
		{
			usleep(100);
			if (gettimeofday(&stamp, NULL))
				continue ;
			now = stamp.tv_sec * 1000 + stamp.tv_usec / 1000;
		}
		return ;
	}
}

int			ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void		ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	return ;
}

int			ft_atoi(char *str, size_t *nbr)
{
	if (*str == '\0')
		return (-1);
	*nbr = 0;
	while (*str >= '0' && *str <= '9')
		*nbr = *nbr * 10 + (*str++ - 48);
	if (*str != '\0')
		return (-1);
	if (nbr <= 0)
		return (-1);
	return (0);
}
