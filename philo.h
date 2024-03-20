/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:49:13 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/20 18:00:59 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;
typedef struct s_data	t_data;
typedef unsigned long	t_time;

typedef struct s_args
{
	char				**argument_list;
	unsigned int		num_philos;
	t_time				time_to_die;
	t_time				time_to_eat;
	t_time				time_to_sleep;
	int					max_eat_times;
}						t_args;

typedef struct s_philo
{
	t_data				*data;
	t_thread			thread;
	int					num;
	t_time				time_last_ate;
	t_time				time_started;
	unsigned int		meals_consumed;
	int					max_eat_times;
	bool				is_dead;
	bool				is_eating;
	t_mutex				*fork_1;
	t_mutex				*fork_2;
}						t_philo;

struct					s_data
{
	t_args				*args;
	t_philo				*philos;
	t_mutex				*forks;
	t_mutex				write_lock;
	t_mutex				stop_lock;
	t_mutex				meal_update_lock;
	t_thread			monitor;
	t_time				time_started;
	bool				terminate;
};

int						parse_args(t_args *args, char *argv[]);
int						ft_atoi(const char *str);
int						ft_error(char *msg);
char					**ft_split(char const *s, char c);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
size_t					ft_strlen(const char *str);
void					free_args(char **arguments);
t_time					get_time(void);
void					*monitor_routine(void *arg);
void					accurate_usleep(t_time milliseconds);
void					log_msg(char *msg, t_philo *philo);
bool					should_stop(t_philo *philo);

#endif
