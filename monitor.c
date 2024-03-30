/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:05:50 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/30 23:12:40 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_philo_dead(t_philo *philo)
{
	t_time	time_to_die;

	time_to_die = philo->data->args->time_to_die;
	pthread_mutex_lock(&philo->data->meal_update_lock);
	if (!philo->is_eating && get_time() - philo->time_last_ate >= time_to_die)
		return (pthread_mutex_unlock(&philo->data->meal_update_lock), true);
	pthread_mutex_unlock(&philo->data->meal_update_lock);
	return (false);
}

// Checks if all the philosophers are alive
// Takes in the array of philosophers as a parameter
bool	are_philos_alive(t_philo *philos)
{
	unsigned int	i;
	unsigned int	num_philos;

	i = 0;
	num_philos = philos->data->args->num_philos;
	while (i < num_philos)
	{
		if (is_philo_dead(&philos[i]))
		{
			log_msg("died", &philos[i]);
			pthread_mutex_lock(&philos->data->stop_lock);
			philos[i].is_dead = true;
			philos->data->terminate = true;
			pthread_mutex_unlock(&philos->data->stop_lock);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	are_philos_full(t_philo *philos)
{
	unsigned int	i;
	unsigned int	num_full_philos;

	i = 0;
	num_full_philos = 0;
	if (philos->max_eat_times == -1)
		return (false);
	while (i < philos->data->args->num_philos)
	{
		pthread_mutex_lock(&philos->data->meal_update_lock);
		if ((int)philos[i].meals_consumed >= philos->max_eat_times)
			num_full_philos++;
		pthread_mutex_unlock(&philos->data->meal_update_lock);
		i++;
	}
	if (num_full_philos == philos->data->args->num_philos)
	{
		pthread_mutex_lock(&philos->data->stop_lock);
		philos->data->terminate = true;
		pthread_mutex_unlock(&philos->data->stop_lock);
		return (true);
	}
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (are_philos_alive(philos) && !are_philos_full(philos))
		continue ;
	// puts("Monitor stopping");
	return (NULL);
}
