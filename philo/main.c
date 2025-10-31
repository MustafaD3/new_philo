/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 02:28:16 by mdalkili          #+#    #+#             */
/*   Updated: 2025/10/31 04:44:12 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid_argument(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	init_monitor(t_monitor *monitor)
{
	monitor->stop = 0;
	if (pthread_mutex_init(&monitor->dead_lock, NULL) != 0)
		return (printf("Dead Lock Mutex Inıt error"), 0);
	if (pthread_mutex_init(&monitor->meal_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&monitor->dead_lock);
		return (printf("Meal Lock Mutex Inıt error"), 0);
	}
	return (1);
}

int	init_philos(char **argv, t_monitor *monitor)
{
	int	i;

	i = 0;
	monitor->philos = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!monitor->philos)
		return (printf("Malloc Error"), 0);
	while (i < ft_atoi(argv[1]))
	{
		monitor->philos[i].id = i + 1;
		monitor->philos[i].time_to_die = ft_atoi(argv[2]);
		monitor->philos[i].time_to_eat = ft_atoi(argv[3]);
		monitor->philos[i].time_to_sleep = ft_atoi(argv[4]);
		monitor->philos[i].meals_eaten = 0;
		monitor->philos[i].l_fork = &monitor->forks[i];
		monitor->philos[i].r_fork = &monitor->forks[(i + 1)
			% monitor->num_of_philos];
		monitor->philos[i].monitor = monitor;
		i++;
	}
	if (argv[5])
		monitor->number_of_must_eat = ft_atoi(argv[5]);
	else
		monitor->number_of_must_eat = -1;
	return (1);
}

static int	validate(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_valid_argument(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_monitor	monitor;

	if (argc != 5 && argc != 6)
	{
		printf("Invalid argument count!\n");
		return (1);
	}
	if (!validate(argv))
	{
		printf("Invalid argument error!\n");
		return (1);
	}
	if (!initialize(&monitor, argv))
		return (1);
	if (!create_threads(&monitor) || !join_threads(&monitor))
		return (1);
	return (0);
}
