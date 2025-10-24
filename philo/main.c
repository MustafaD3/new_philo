/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:16:30 by mdalkili          #+#    #+#             */
/*   Updated: 2025/10/23 18:42:34 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid_argument(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	if (!ft_is_digit(str[i]))
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_is_digit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	init_sim(t_sim *sim, char **argv)
{
	sim->num_of_philos = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		sim->number_of_must_eat = ft_atoi(argv[5]);
	else
		sim->number_of_must_eat = -1;
	sim->died = 0;
	sim->total_philos = 0;
	pthread_mutex_init(&sim->meal_lock, NULL);
	pthread_mutex_init(&sim->total_philos_lock, NULL);
}

static int	validate_and_initialize(char **argv, t_sim *sim)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_valid_argument(argv[i]))
			return (1);
		i++;
	}
	init_sim(sim, argv);
	if (sim->num_of_philos < 1 || sim->num_of_philos > PHILO_MAX
		|| sim->time_to_die <= 0 || sim->time_to_eat <= 0
		|| sim->time_to_sleep <= 0)
		return (1);
	if (argv[5] && sim->number_of_must_eat <= 0)
		return (1);
	sim->start_time = get_current_time();
	return (0);
}

int	main(int ac, char **av)
{
	t_sim	sim;

	if (ac != 5 && ac != 6)
		ft_error("Invalid argument count!\n");
	if (validate_and_initializea(av, &sim))
		ft_error("Invalid argument error!\n");
	init_forks(&sim);
	init_philos(&sim);
	start_threads(&sim);
	destroy_mutexes(NULL, &sim);
	return (0);
}
