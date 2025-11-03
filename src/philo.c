/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 03:45:08 by mdalkili          #+#    #+#             */
/*   Updated: 2025/11/01 04:03:08 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	stop_control(t_philo *philo)
{
	if (philo->monitor->stop)
	{
		pthread_mutex_unlock(&philo->monitor->dead_lock);
		if (philo->has_left_fork)
			pthread_mutex_unlock(philo->l_fork);
		if (philo->has_right_fork)
			pthread_mutex_unlock(philo->r_fork);
		philo->has_left_fork = 0;
		philo->has_right_fork = 0;
		return (philo->monitor->stop);
	}
	return (0);
}

static void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_philo_status(philo, "has taken a fork");
	ft_usleep(philo->time_to_die, philo);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_lock(&philo->monitor->dead_lock);
	philo->monitor->stop = 1;
	pthread_mutex_unlock(&philo->monitor->dead_lock);
}

static void	eat_and_sleep(t_philo *philo)
{
	if (is_philo_dead(philo))
		return ;
	pthread_mutex_lock(&philo->monitor->meal_lock);
	philo->meals_eaten++;
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->monitor->meal_lock);
	print_philo_status(philo, "is eating");
	ft_usleep(philo->time_to_eat, philo);
	if (philo->has_left_fork)
	{
		pthread_mutex_unlock(philo->l_fork);
		philo->has_left_fork = 0;
	}
	if (philo->has_right_fork)
	{
		pthread_mutex_unlock(philo->r_fork);
		philo->has_right_fork = 0;
	}
	print_philo_status(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep, philo);
	print_philo_status(philo, "is thinking");
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->monitor->num_of_philos == 1)
		return (one_philo(philo), NULL);
	if (philo->id % 2 == 0)
		usleep(philo->time_to_eat * 500);
	while (1)
	{
		get_forks(philo);
		pthread_mutex_lock(&philo->monitor->dead_lock);
		if (stop_control(philo))
			break ;
		pthread_mutex_unlock(&philo->monitor->dead_lock);
		if (is_philo_dead(philo))
			return (NULL);
		if (philo->has_left_fork && philo->has_right_fork)
			eat_and_sleep(philo);
		else
			break ;
	}
	return (NULL);
}

int	initialize(t_monitor *monitor, char **argv)
{
	monitor->num_of_philos = ft_atoi(argv[1]);
	if (pthread_mutex_init(&monitor->write_lock, NULL) != 0)
		return (printf("Write Lock Init Error"), 0);
	if (!init_forks(monitor))
		return (0);
	if (!init_philos(argv, monitor))
		return (0);
	if (!init_monitor(monitor))
		return (0);
	return (1);
}
