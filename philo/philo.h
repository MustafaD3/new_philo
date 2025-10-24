/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:16:10 by mdalkili          #+#    #+#             */
/*   Updated: 2025/10/23 18:34:11 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 200

typedef struct s_sim	t_sim;

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	size_t				last_meal;
	pthread_t			thread;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	t_sim				*sim;
}						t_philo;

typedef struct s_sim
{
	int					num_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_must_eat;
	int					total_philos;
	int					died;
	size_t				start_time;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		total_philos_lock;
	pthread_mutex_t		*forks;
	t_philo				*philos;
	struct timeval		begin_time;
}						t_sim;

void					init_forks(t_sim *sim);
void					init_philos(t_sim *sim);
void					destroy_mutexes(char *str, t_sim *sim);
void					start_threads(t_sim *sim);
long					get_current_time(void);
void					*philo_routine(void *arg);
int						philo_has_died(t_philo *philo);
void					print_log(t_philo *philo, char *status);
void					get_forks(t_philo *philo);
void					ft_usleep(long time_in_ms, t_philo *philo);
void					*ft_monitor(void *arg);
int						ft_strlen(char *str);
int						ft_atoi(const char *str);
bool					ft_is_digit(char c);
bool					ft_isspace(char c);
void					ft_error(const char *str);

#endif