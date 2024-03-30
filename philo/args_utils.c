/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:23:44 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/30 23:25:14 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Joins two strings with a space in between
char	*strjoin(char *s1, char *s2)
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
char	*join_args(char *argv[])
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
