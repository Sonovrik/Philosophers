/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 17:36:12 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/16 20:31:08 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			print_error(int error)
{
	if (error == WRONG_ARGS)
		ft_putstr_fd("Error: wrong arguments\n", 2);
	else if (error == MALLOC_ERROR)
		ft_putstr_fd("Error: malloc error\n", 2);
	return (error);
}

int		get_size_value(size_t nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
		len++;
	else
	{
		while (nbr != 0)
		{
			len++;
			nbr /= 10;
		}
	}
	return (len);
}

int		get_all_size(size_t val_time, size_t number, char *text)
{
	int	len;

	len = 0;
	len += get_size_value(val_time) + 1;
	len += get_size_value(number) + 1;
	len += ft_strlen(text);
	return (len);
}

int		str_val_time(char *str, size_t val_time)
{
	int	i;
	int	len;

	i = 0;
	len = get_size_value(val_time) + 1;
	i = len - 1;
	str[i] = ' ';
	while (--i >= 0)
	{
		str[i] = val_time % 10 + 48;
		val_time /= 10;
	}
	return (len);
}


void		str_text(char *str, char *text)
{
	int	i;

	i = 0;
	while (text[i] != '\0')
	{
		str[i] = text[i];
		i++;
	}
	return ;
}

void	init_string(size_t val_time, size_t number, char *text)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = get_all_size(val_time, number, text);
	if ((str = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return ;
	str[len] = '\0';
	i += str_val_time(&str[i], val_time);
	i += str_val_time(&str[i], number);
	str_text(&str[i], text);
	ft_putstr_fd(str, 1);
	free(str);
}
void	view_status(t_philo *philo, int action)
{
	struct timeval	time;
	size_t			val_time;

	gettimeofday(&time, NULL);
	// val_time = (size_t)((time.tv_sec - philo->live_time->tv_sec) * 1000
	// 	+ (time.tv_usec - philo->live_time->tv_usec) / 1000);
	val_time = (size_t)(time.tv_sec * 1000 + time.tv_usec / 1000 - philo->start_sim);
	if (action == TOOK_FORK_LEFT)
		init_string(val_time, philo->number, "has taken left fork\n");
	else if (action == TOOK_FORK_RIGHT)
		init_string(val_time, philo->number, "has taken right fork\n");
	else if (action == PUT_FORK_LEFT)
		init_string(val_time, philo->number, "has drop left fork\n");
	else if (action == PUT_FORK_RIGHT)
		init_string(val_time, philo->number, "has drop right fork\n");
	else if (action == SLEEPING)
		init_string(val_time, philo->number, "is sleeping\n");
	else if (action == EATING)
		init_string(val_time, philo->number, "is eating\n");
	else if (action == THINKING)
		init_string(val_time, philo->number, "is thinking\n");
	else if (action == DIED)
		init_string(val_time, philo->number, "died\n");
	
}
