/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:49:13 by maabdull          #+#    #+#             */
/*   Updated: 2024/04/01 14:21:27 by maabdull         ###   ########.fr       */
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

bool					check_overflow(const char *str, unsigned long num);
int						ft_atoi(const char *str);
int						ft_error(char *msg);
char					**ft_split(char const *s, char c);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
size_t					ft_strlen(const char *str);
char					*strjoin(char *s1, char *s2);
char					*join_args(char *argv[]);
void					free_args(char **arguments);
int						parse_args(t_args *args, char *argv[]);
int						init_data(t_data *data);
int						init_philos(t_data *data);
t_time					get_time(void);
void					*monitor_routine(void *arg);
void					accurate_usleep(t_time milliseconds, t_data *data);
void					log_msg(char *msg, t_philo *philo);
bool					should_stop(t_philo *philo);
int						stop_threads(t_data *data);
void					destroy_forks(t_data *data);

#endif
