/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:36:36 by maabdull          #+#    #+#             */
/*   Updated: 2024/04/02 12:24:22 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	free_data(&data);
	return (0);
}
