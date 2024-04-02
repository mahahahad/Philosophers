/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:17:13 by maabdull          #+#    #+#             */
/*   Updated: 2024/04/01 14:21:02 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static int	ft_issign(char c)
{
	return (c == '+' || c == '-');
}

int	ft_atoi(const char *str)
{
	unsigned long	num;
	int				sign;
	int				i;

	num = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (ft_issign(str[i]))
		i++;
	str += i;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			num = (num * 10) + str[i++] - '0';
		else
			break ;
	}
	if (check_overflow(str, (sign * num)))
		return (-1);
	return (sign * num);
}

int	ft_error(char *msg)
{
	printf("Error\n%s\n", msg);
	return (EXIT_FAILURE);
}
