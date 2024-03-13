/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:17:13 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/13 11:50:39 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static inline int	ft_issign(char c)
{
	return (c == '+' || c == '-');
}

int	ft_atoi(const char *str)
{
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		sign = -1;
	if (ft_issign(*str))
		str++;
	while (*str)
	{
		if (ft_isdigit(*str))
			num = (num * 10) + *(str++) - '0';
		else
			break ;
	}
	return (sign * num);
}

int	ft_error(char *msg)
{
	printf("Error\n%s\n", msg);
	return (EXIT_FAILURE);
}
