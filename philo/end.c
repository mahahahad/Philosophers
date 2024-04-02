/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:30:29 by maabdull          #+#    #+#             */
/*   Updated: 2024/04/02 12:24:08 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(t_data *data)
{
	free_args(data->args->argument_list);
	free(data->philos);
	free(data->forks);
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
