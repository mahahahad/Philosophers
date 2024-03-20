/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:24:32 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/20 23:02:43 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	should_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->stop_lock);
	if (philo->is_dead || philo->data->terminate)
		return (pthread_mutex_unlock(&philo->data->stop_lock), true);
	pthread_mutex_unlock(&philo->data->stop_lock);
	return (false);
}

void	log_msg(char *msg, t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->write_lock);
	if (should_stop(philo))
	{
		pthread_mutex_unlock(&data->write_lock);
		return ;
	}
	printf("%lu %d %s\n", get_time() - philo->time_started, philo->num, msg);
	pthread_mutex_unlock(&data->write_lock);
}
