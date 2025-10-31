/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 04:36:42 by mdalkili          #+#    #+#             */
/*   Updated: 2025/10/29 04:30:43 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	get_forks(t_philo *philo)
{
	if (is_philo_dead(philo))
		return ;
	if (philo->id % 2 == 1)
	{
		usleep(500);
		pthread_mutex_lock(philo->l_fork);
		print_philo_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		print_philo_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_philo_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		print_philo_status(philo, "has taken a fork");
	}
}
