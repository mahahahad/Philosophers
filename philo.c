/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:36:36 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/13 11:59:57 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_args	args;
	// t_data	data;

	if (argc == 1 || parse_args(&args, ++argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	free_args(args.argument_list);
	// data.args = &args;
}
