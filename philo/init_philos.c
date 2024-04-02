/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:29:21 by maabdull          #+#    #+#             */
/*   Updated: 2024/04/01 15:43:10 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_eat(t_philo *philo)
{
	if (pthread_mutex_lock(philo->fork_2))
		printf("Locking mutex fork 2 failed\n");
	log_msg("has taken a fork", philo);
	if (philo->data->args->num_philos == 1)
	{
		accurate_usleep(philo->data->args->time_to_die, philo->data);
		pthread_mutex_unlock(philo->fork_2);
		return ;
	}
	if (pthread_mutex_lock(philo->fork_1))
		printf("Locking mutex fork 1 failed\n");
	log_msg("has taken a fork", philo);
	pthread_mutex_lock(&philo->data->meal_update_lock);
	philo->is_eating = true;
	pthread_mutex_unlock(&philo->data->meal_update_lock);
	log_msg("is eating", philo);
	pthread_mutex_lock(&philo->data->meal_update_lock);
	philo->is_eating = false;
	philo->time_last_ate = get_time();
	philo->meals_consumed++;
	pthread_mutex_unlock(&philo->data->meal_update_lock);
	accurate_usleep(philo->data->args->time_to_eat, philo->data);
	pthread_mutex_unlock(philo->fork_2);
	pthread_mutex_unlock(philo->fork_1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num % 2 == 0)
		accurate_usleep(1, philo->data);
	while (!should_stop(philo))
	{
		p_eat(philo);
		log_msg("is sleeping", philo);
		accurate_usleep(philo->data->args->time_to_sleep, philo->data);
		log_msg("is thinking", philo);
	}
	return (NULL);
}

int	init_philos(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->args->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, routine,
				&data->philos[i]))
			return (ft_error("Failed to create thread"), EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
