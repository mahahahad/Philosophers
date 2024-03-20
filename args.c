/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:42:13 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/20 19:44:39 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Joins two strings with a space in between
static char	*strjoin(char *s1, char *s2)
{
	char	*final_str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	final_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!final_str)
		return (NULL);
	while (s1[++i])
		final_str[i] = s1[i];
	if (s1[i] == '\0')
		final_str[i++] = ' ';
	while (s2[j])
		final_str[i++] = s2[j++];
	final_str[i] = '\0';
	return (final_str);
}

// Joins arguments separating them with a space
static char	*join_args(char *argv[])
{
	int		i;
	char	*joined_args;
	char	*temp;

	i = 0;
	joined_args = malloc(1);
	if (!joined_args)
		return (NULL);
	joined_args[0] = '\0';
	temp = NULL;
	while (argv[i])
	{
		temp = joined_args;
		joined_args = strjoin(joined_args, argv[i]);
		if (!joined_args)
			return (free(temp), NULL);
		free(temp);
		temp = NULL;
		i++;
	}
	return (joined_args);
}

// Frees the double pointer containing the string arguments
void	free_args(char **arguments)
{
	int	i;

	i = 0;
	while (arguments[i])
		free(arguments[i++]);
	free(arguments);
	arguments = NULL;
}

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
	if (ft_atoi(arg_list[0]) < 1)
		return (ft_error("Philo count must be positive"), EXIT_FAILURE);
	args->num_philos = ft_atoi(arg_list[0]);
	if (ft_atoi(arg_list[1]) < 0 || ft_atoi(arg_list[2]) < 0
		|| ft_atoi(arg_list[3]) < 0)
		return (ft_error("Time must be positive"), EXIT_FAILURE);
	args->time_to_die = ft_atoi(arg_list[1]);
	args->time_to_eat = ft_atoi(arg_list[2]);
	args->time_to_sleep = ft_atoi(arg_list[3]);
	if (arg_list[4])
		if (ft_atoi(arg_list[4]) < 0)
			return (ft_error("Max meal count must be positive"), EXIT_FAILURE);
		else
			args->max_eat_times = ft_atoi(arg_list[4]);
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
