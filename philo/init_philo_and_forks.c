/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:16:34 by mdalkili          #+#    #+#             */
/*   Updated: 2025/10/23 18:34:45 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_forks(t_philo *philo)
{
	if (philo_has_died(philo))
		return ;
	if (philo->id % 2 == 1)
	{
		usleep(500);
		pthread_mutex_lock(philo->l_fork);
		print_log(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		print_log(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_log(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		print_log(philo, "has taken a fork");
	}
}

void	init_forks(t_sim *sim)
{
	int	i;

	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->num_of_philos);
	if (!sim->forks)
		ft_error("Error in the forks\n");
	i = 0;
	while (i < sim->num_of_philos)
	{
		pthread_mutex_init(&sim->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&sim->write_lock, NULL);
	pthread_mutex_init(&sim->dead_lock, NULL);
}

void	init_philos(t_sim *sim)
{
	int			i;

	sim->philos = malloc(sizeof(t_philo) * sim->num_of_philos);
	if (!sim->philos)
		ft_error("Memory error!\n");
	sim->start_time = get_current_time();
	i = 0;
	while (i < sim->num_of_philos)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].meals_eaten = 0;
		sim->philos[i].last_meal = sim->start_time;
		sim->philos[i].sim = sim;
		sim->philos[i].l_fork = &sim->forks[i];
		sim->philos[i].r_fork = &sim->forks[(i + 1) % sim->num_of_philos];
		i++;
	}
}
