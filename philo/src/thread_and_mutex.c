/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_and_mutex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 03:13:09 by mdalkili          #+#    #+#             */
/*   Updated: 2025/10/31 05:20:17 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_forks(t_monitor *monitor)
{
	int	i;

	monitor->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* monitor->num_of_philos);
	if (!monitor->forks)
	{
		printf("Malloc Error\n");
		return (0);
	}
	i = 0;
	while (i < monitor->num_of_philos)
	{
		if (pthread_mutex_init(&monitor->forks[i], NULL) != 0)
		{
			printf("Mutex Init Error\n");
			while (--i >= 0)
				pthread_mutex_destroy(&monitor->forks[i]);
			free(monitor->forks);
			return (0);
		}
		i++;
	}
	return (1);
}

int	create_threads(t_monitor *monitor)
{
	int	i;

	i = 0;
	monitor->start_time = get_current_time();
	while (i < monitor->num_of_philos)
	{
		pthread_mutex_lock(&monitor->meal_lock);
		monitor->philos[i].last_meal = monitor->start_time;
		pthread_mutex_unlock(&monitor->meal_lock);
		if (pthread_create(&monitor->philos[i].thread, NULL, philo_routine
				, (void *)&monitor->philos[i]) != 0)
		{
			printf("Thread Create Error\n");
			return (0);
		}
		i++;
	}
	if (pthread_create(&monitor->thread, NULL, monitor_f, (void *)monitor) != 0)
	{
		printf("Thread Create Error\n");
		return (0);
	}
	return (1);
}

int	join_threads(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->num_of_philos)
	{
		if (pthread_join(monitor->philos[i].thread, NULL) != 0)
		{
			printf("Thread Join Error\n");
			return (0);
		}
		i++;
	}
	if (pthread_join(monitor->thread, NULL) != 0)
	{
		printf("Thread Join Error\n");
		return (0);
	}
	return (1);
}
