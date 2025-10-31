/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 03:57:53 by mdalkili          #+#    #+#             */
/*   Updated: 2025/10/31 04:47:10 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_philo_dead(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->monitor->dead_lock);
	result = philo->monitor->stop;
	pthread_mutex_unlock(&philo->monitor->dead_lock);
	return (result);
}

static int	all_philosophers_eat_the_maximum(t_monitor *monitor)
{
	int	i;
	int	total;

	if (monitor->number_of_must_eat < 0)
		return (0);
	i = 0;
	total = 0;
	while (i < monitor->num_of_philos)
	{
		pthread_mutex_lock(&monitor->meal_lock);
		if (monitor->philos[i].meals_eaten >= monitor->number_of_must_eat)
			total++;
		pthread_mutex_unlock(&monitor->meal_lock);
		i++;
	}
	if (total == monitor->num_of_philos)
	{
		pthread_mutex_lock(&monitor->dead_lock);
		monitor->stop = 1;
		pthread_mutex_unlock(&monitor->dead_lock);
		return (1);
	}
	return (0);
}

static int	any_philosopher_died(t_monitor *monitor)
{
	int			i;
	long		current_time;
	long		last_meal;

	i = 0;
	current_time = get_current_time();
	while (i < monitor->num_of_philos)
	{
		pthread_mutex_lock(&monitor->meal_lock);
		last_meal = monitor->philos[i].last_meal;
		pthread_mutex_unlock(&monitor->meal_lock);
		if (current_time - last_meal >= monitor->philos[i].time_to_die)
		{
			pthread_mutex_lock(&monitor->dead_lock);
			monitor->stop = 1;
			printf("%ld %d died\n", get_current_time()
				- monitor->start_time, monitor->philos[i].id);
			pthread_mutex_unlock(&monitor->dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor_f(void *arg)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)arg;
	while (1)
	{
		if (any_philosopher_died(monitor)
			|| all_philosophers_eat_the_maximum(monitor))
			break ;
		usleep(1000);
	}
	return (NULL);
}
