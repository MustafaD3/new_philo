/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:16:23 by mdalkili          #+#    #+#             */
/*   Updated: 2025/10/23 18:16:24 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_and_print(t_philo *philo)
{
	int		required_meals;

	required_meals = philo->sim->number_of_must_eat;
	if (required_meals != -1
		&& philo->meals_eaten == required_meals)
	{
		pthread_mutex_lock(&philo->sim->total_philos_lock);
		philo->sim->total_philos++;
		if (philo->sim->total_philos == philo->sim->num_of_philos)
		{
			pthread_mutex_lock(&philo->sim->dead_lock);
			philo->sim->died = 1;
			pthread_mutex_unlock(&philo->sim->dead_lock);
		}
		pthread_mutex_unlock(&philo->sim->total_philos_lock);
	}
}

void	philo_eat(t_philo *philo)
{
	get_forks(philo);
	pthread_mutex_lock(&philo->sim->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->sim->meal_lock);
	print_log(philo, "is eating");
	ft_usleep(philo->sim->time_to_eat, philo);
	pthread_mutex_lock(&philo->sim->meal_lock);
	check_and_print(philo);
	pthread_mutex_unlock(&philo->sim->meal_lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_sleep(t_philo *philo)
{
	if (philo_has_died(philo))
		return ;
	print_log(philo, "is sleeping");
	ft_usleep(philo->sim->time_to_sleep, philo);
	if (philo_has_died(philo))
		return ;
	print_log(philo, "is thinking");
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->sim->num_of_philos == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		print_log(philo, "has taken a fork");
		ft_usleep(philo->sim->time_to_die, philo);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_lock(&philo->sim->dead_lock);
		philo->sim->died = 1;
		pthread_mutex_unlock(&philo->sim->dead_lock);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->sim->time_to_eat / 10, philo);
	while (!philo_has_died(philo))
	{
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}
