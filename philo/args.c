/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:42:13 by maabdull          #+#    #+#             */
/*   Updated: 2024/04/01 14:11:27 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(char **arg_list)
{
	int	i;

	i = 0;
	while (arg_list[i])
		i++;
	if (i != 4 && i != 5)
		return (ft_error("Invalid arguments"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	assign_args(t_args *args, char **arg_list)
{
	args->num_philos = ft_atoi(arg_list[0]);
	args->time_to_die = ft_atoi(arg_list[1]);
	args->time_to_eat = ft_atoi(arg_list[2]);
	args->time_to_sleep = ft_atoi(arg_list[3]);
	if ((int) args->num_philos <= 0 || (long) args->time_to_die <= 0
		|| (long) args->time_to_eat <= 0 || (long) args->time_to_sleep <= 0)
		return (ft_error("Please enter valid inputs"), EXIT_FAILURE);
	if (arg_list[4])
	{
		args->max_eat_times = ft_atoi(arg_list[4]);
		if (args->max_eat_times <= 0)
			return (ft_error("Max meal count must be positive"), EXIT_FAILURE);
	}
	else
		args->max_eat_times = -1;
	return (EXIT_SUCCESS);
}

/**
 * @brief Parse the user provided arguments into valid arguments
 *
 * @param args The data structure containing the valid arguments
 * @param argv
 */
int	parse_args(t_args *args, char *argv[])
{
	char	*joined_args;

	joined_args = join_args(argv);
	if (!joined_args)
		return (ft_error("Failed to parse arguments"), EXIT_FAILURE);
	args->argument_list = ft_split(joined_args, ' ');
	free(joined_args);
	if (!args->argument_list)
		return (ft_error("Failed to split arguments"), EXIT_FAILURE);
	if (check_args(args->argument_list) == EXIT_FAILURE)
		return (free_args(args->argument_list), EXIT_FAILURE);
	if (assign_args(args, args->argument_list) == EXIT_FAILURE)
		return (free_args(args->argument_list), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
