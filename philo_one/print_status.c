/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 17:36:12 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/13 22:35:29 by lmidori          ###   ########.fr       */
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
	len += get_size_value(val_time + 1);
	len += get_size_value(number + 1);
	len += ft_strlen(text);
	return (len);
}

void	init_string(int len, size_t val_time, size_t number, char *text)
{
	int		i;
	int		len;
	char	*str;
	int		tmp;

	i = 0;
	len = get_all_size(val_time, number, text);
	str = (char *)malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	tmp = get_size_value(val_time);
	while (tmp > 0)
	{
		str[tmp - 1] = val_time % 10 + 48;
		val_time /= 10;
		tmp--;
	}
	
	
	
}

void	view_status(t_philo *philo, int action)
{
	int	len;
	struct timeval	time;
	size_t			val_time;
	char			*str;

	len = 0;
	gettimeofday(&time, NULL);
	val_time = (size_t)((time.tv_sec - philo->live_time->tv_sec) * 1000
		+ (time.tv_usec - philo->live_time->tv_usec) / 1000);
	len += get_size_value(val_time);
	len += get_size_value((size_t)philo->number);
	if (action == TOOK_FORK_LEFT)
		
	else if (action == TOOK_FORK_RIGHT)

	else if (action == PUT_FORK_LEFT)

	else if (action == PUT_FORK_RIGHT)

	else if (action == SLEEPING)

	else if (action == EATING)

	else if (action == THINKING)

	else if (action == DIED)

	
	str = (char *)malloc(sizeof(char) * (len + 4));
}

void	view_status(t_philo *philo, int action)
{
	char	*str;
	struct timeval time;
	size_t	val_time;
	
	gettimeofday(&time, NULL);

	val_time = (size_t)((time.tv_sec - philo->live_time->tv_sec) * 1000
		+ (time.tv_usec - philo->live_time->tv_usec) / 1000);
	// char	*tmp;
	// char	*tmp2;
	
	str = ft_putnbr_fd(philo->number);
	ft_putstr_fd("timestamp_in_ms ", 1);
	// philo = NULL;
	if (action == TOOK_FORK_LEFT)
		ft_putstr_fd(" has taken left fork\n", 1);
	else if (action == TOOK_FORK_RIGHT)
		ft_putstr_fd(" has taken right fork\n", 1);
	else if (action == PUT_FORK_LEFT)
		ft_putstr_fd(" has drop left fork\n", 1);
	else if (action == PUT_FORK_RIGHT)
		ft_putstr_fd(" has drop right fork\n", 1);
	else if (action == SLEEPING)
		ft_putstr_fd(" is sleeping\n", 1);
	else if (action == EATING)
		ft_putstr_fd(" is eating\n", 1);
	else if (action == THINKING)
		ft_putstr_fd(" is thinking\n", 1);
	else if (action == DIED)
		ft_putstr_fd(" died\n", 1);
}