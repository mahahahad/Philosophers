/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:36:36 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/30 23:12:13 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_eat(t_philo *philo)
{
	// if (philo->num == 1)
	// {
		if (pthread_mutex_lock(philo->fork_2))
			printf("Locking mutex fork 2 failed");
		log_msg("has taken a fork", philo);
		if (philo->data->args->num_philos == 1)
		{
			accurate_usleep(philo->data->args->time_to_die);
			pthread_mutex_unlock(philo->fork_2);
			return ;
		}
		if (pthread_mutex_lock(philo->fork_1))
			printf("Locking mutex fork 1 failed");
		log_msg("has taken a fork", philo);
	// }
	// else
	// {
	// 	if (pthread_mutex_lock(philo->fork_1))
	// 		printf("Locking mutex fork 1 failed");
	// 	log_msg("has taken a fork", philo);
	// 	if (pthread_mutex_lock(philo->fork_2))
	// 		printf("Locking mutex fork 2 failed");
	// 	log_msg("has taken a fork", philo);
	// }
	philo->is_eating = true;
	log_msg("is eating", philo);
	pthread_mutex_lock(&philo->data->meal_update_lock);
	philo->is_eating = false;
	philo->time_last_ate = get_time();
	philo->meals_consumed++;
	pthread_mutex_unlock(&philo->data->meal_update_lock);
	accurate_usleep(philo->data->args->time_to_eat);
	pthread_mutex_unlock(philo->fork_2);
	pthread_mutex_unlock(philo->fork_1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num % 2 == 0)
		accurate_usleep(1);
	while (!should_stop(philo))
	{
		p_eat(philo);
		log_msg("is sleeping", philo);
		accurate_usleep(philo->data->args->time_to_sleep);
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

int	stop_threads(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->args->num_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return (EXIT_FAILURE);
		i++;
	}
	if (pthread_join(data->monitor, NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	destroy_forks(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->args->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_args	args;
	t_data	data;

	if (argc == 1 || parse_args(&args, ++argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	data.args = &args;
	if (init_data(&data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	stop_threads(&data);
	destroy_forks(&data);
	pthread_mutex_destroy(&data.write_lock);
	pthread_mutex_destroy(&data.stop_lock);
	pthread_mutex_destroy(&data.meal_update_lock);
	free_args(args.argument_list);
	free(data.philos);
	free(data.forks);
}
