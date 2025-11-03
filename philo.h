/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 05:20:52 by mdalkili          #+#    #+#             */
/*   Updated: 2025/11/01 03:36:16 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_monitor	t_monitor;

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					is_die;
	int					has_left_fork;
	int					has_right_fork;
	pthread_t			thread;
	long				last_meal;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	t_monitor			*monitor;
}						t_philo;

typedef struct s_monitor
{
	int					num_of_philos;
	int					number_of_must_eat;
	long				start_time;
	int					stop;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		*forks;
	t_philo				*philos;
	pthread_t			thread;
}						t_monitor;

int		ft_atoi(const char *str);
int		ft_strlen(char *str);
long	get_current_time(void);
void	ft_usleep(long time_in_ms, t_philo *philo);
int		create_threads(t_monitor *monitor);
int		join_threads(t_monitor *monitor);
void	print_philo_status(t_philo *philo, char *str);
int		is_philo_dead(t_philo *philo);
int		init_forks(t_monitor *monitor);
int		init_philos(char **argv, t_monitor *monitor);
int		initialize(t_monitor *monitor, char **argv);
int		init_monitor(t_monitor *monitor);
void	*philo_routine(void *arg);
void	*monitor_f(void *arg);
void	get_forks(t_philo *philo);
void	free_all(t_monitor *monitor);
#endif