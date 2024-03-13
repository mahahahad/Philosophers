/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:49:13 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/13 11:51:28 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;

typedef struct s_args
{
	char				**argument_list;
	int					num_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_eat_times;
}						t_args;

typedef struct s_data
{
	t_args				*args;
}						t_data;

int						parse_args(t_args *args, char *argv[]);
int						ft_atoi(const char *str);
int						ft_error(char *msg);
char					**ft_split(char const *s, char c);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
size_t					ft_strlen(const char *str);
void					free_args(char **arguments);

#endif
