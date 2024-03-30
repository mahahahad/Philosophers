/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:28:35 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/30 23:33:14 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->args->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	init_philos_data(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->args->num_philos)
	{
		data->philos[i].data = data;
		data->philos[i].num = i + 1;
		data->philos[i].max_eat_times = data->args->max_eat_times;
		data->philos[i].meals_consumed = 0;
		data->philos[i].is_dead = false;
		data->philos[i].is_eating = false;
		data->philos[i].time_started = get_time();
		data->philos[i].time_last_ate = get_time();
		data->philos[i].fork_1 = &data->forks[i];
		if (i == data->args->num_philos - 1)
			data->philos[i].fork_2 = &data->forks[0];
		else
			data->philos[i].fork_2 = &data->forks[i + 1];
		i++;
	}
}

int	init_data(t_data *data)
{
	data->time_started = get_time();
	data->philos = malloc(sizeof(t_philo) * data->args->num_philos);
	if (!data->philos)
		return (ft_error("Could not allocate space"), EXIT_FAILURE);
	data->forks = malloc(sizeof(t_mutex) * data->args->num_philos);
	if (!data->forks)
		return (free(data->philos), ft_error("Could not allocate space"),
			EXIT_FAILURE);
	data->terminate = false;
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->stop_lock, NULL);
	pthread_mutex_init(&data->meal_update_lock, NULL);
	if (init_forks(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_philos_data(data);
	if (pthread_create(&data->monitor, NULL, monitor_routine, data->philos))
		return (EXIT_FAILURE);
	if (init_philos(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
