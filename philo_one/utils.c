/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:19:27 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/10 17:35:06 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex00.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 2147483647)
		ft_putstr_fd("2147483647", fd);
	else if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd((n % 10) + '0', fd);
	}
	else
		ft_putchar_fd((n % 10) + '0', fd);
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

int			ft_atoi(char *str, size_t *nbr)
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
