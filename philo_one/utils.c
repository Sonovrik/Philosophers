/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:19:27 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/13 20:09:10 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

char	*ft_putnbr_fd(size_t n)
{
	char	*nbr;
	int		len;
	size_t	tmp;

	tmp = n;
	len = 0;
	if (n == 0)
		len = 1;
	else
		while (tmp != 0)
		{
			tmp /= 10;
			len++;
		}
	len++;
	if ((nbr = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	nbr[len] = '\0';
	nbr[--len] = ' ';
	tmp = n;
	while (--len >= 0)
	{
		nbr[len] = tmp % 10 + 48;
		tmp /= 10;
	}
	return (nbr);
}

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	return ;
}

int			ft_atoi(char *str, int *nbr)
{
	if (*str == '\0')
		return (-1);
	*nbr = 0;
	while (*str >= '0' && *str <= '9')
		*nbr = *nbr * 10 + (*str++ - 48);
	if (*str != '\0')
		return (-1);
	return (0);
}
