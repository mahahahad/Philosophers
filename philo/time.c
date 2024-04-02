/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:15:15 by maabdull          #+#    #+#             */
/*   Updated: 2024/04/01 14:42:20 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/**
 * @brief Accurate version of usleep
 * Compare the start time and current time,
 * if it is less than the sleep milliseconds,
 * sleep for 500 microseconds and compare in the next iteration
 *
 * @param milliseconds the amount of milliseconds to sleep
 */
void	accurate_usleep(t_time milliseconds, t_data *data)
{
	t_time	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < milliseconds)
	{
		pthread_mutex_lock(&data->stop_lock);
		if (data->terminate)
		{
			pthread_mutex_unlock(&data->stop_lock);
			break ;
		}
		pthread_mutex_unlock(&data->stop_lock);
		usleep(500);
	}
}

/**
 * @brief Gets the number of seconds and microseconds from epoch time
 * Sums them up and converts them to milliseconds
 *
 * @return t_time current time in milliseconds
 */
t_time	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1e6 + time.tv_usec) / 1000);
}
