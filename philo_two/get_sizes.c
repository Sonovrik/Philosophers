/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sizes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmidori <lmidori@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 16:06:56 by lmidori           #+#    #+#             */
/*   Updated: 2020/11/18 17:06:29 by lmidori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	get_size_value(size_t nbr)
{
	int		len;

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

static int	get_all_size(size_t val_time, size_t number, char *text)
{
	int		len;

	len = 0;
	len += get_size_value(val_time) + 1;
	len += get_size_value(number) + 1;
	len += ft_strlen(text);
	return (len);
}

static int	str_val_time(char *str, size_t val_time)
{
	int		i;
	int		len;

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

static void	str_text(char *str, char *text)
{
	int		i;

	i = 0;
	while (text[i] != '\0')
	{
		str[i] = text[i];
		i++;
	}
	return ;
}

void		init_string(size_t val_time, size_t number, char *text)
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
