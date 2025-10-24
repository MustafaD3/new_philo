/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:16:16 by mdalkili          #+#    #+#             */
/*   Updated: 2025/10/23 18:24:45 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_died(t_philo *philo, size_t time)
{
	int		result;
	long	current_time;
	long	last_meal;

	result = 0;
	current_time = get_current_time();
	pthread_mutex_lock(&philo->sim->meal_lock);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->sim->meal_lock);
	if (current_time - last_meal >= (long)time)
		result = 1;
	return (result);
}

int	check_death_philo(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_of_philos)
	{
		if (philo_died(&sim->philos[i], sim->time_to_die))
		{
			pthread_mutex_lock(&sim->dead_lock);
			sim->died = 1;
			printf("%ld %d died\n", get_current_time()
				- sim->start_time, sim->philos[i].id);
			pthread_mutex_unlock(&sim->dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	count_finished_eating(t_sim *sim)
{
	int	i;
	int	finished;

	finished = 0;
	i = 0;
	while (i < sim->num_of_philos)
	{
		pthread_mutex_lock(&sim->meal_lock);
		if (sim->philos[i].meals_eaten
			>= sim->number_of_must_eat)
			finished++;
		pthread_mutex_unlock(&sim->meal_lock);
		i++;
	}
	return (finished);
}

int	check_all_ate(t_sim *sim)
{
	int	finished;

	if (sim->number_of_must_eat == -1)
		return (0);
	finished = count_finished_eating(sim);
	if (finished == sim->num_of_philos)
	{
		pthread_mutex_lock(&sim->dead_lock);
		sim->died = 1;
		pthread_mutex_unlock(&sim->dead_lock);
		return (1);
	}
	return (0);
}

void	*ft_monitor(void *arg)
{
	t_sim	*sim;

	sim = (t_sim *)arg;
	while (1)
	{
		if (check_death_philo(sim) || check_all_ate(sim))
			break ;
		usleep(1000);
	}
	return (NULL);
}
