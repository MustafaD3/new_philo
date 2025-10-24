/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:15:46 by mdalkili          #+#    #+#             */
/*   Updated: 2025/10/23 18:16:49 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(const char *str)
{
	printf("%s", str);
	exit(EXIT_FAILURE);
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long time_in_ms, t_philo *philo)
{
	long	start;
	long	now;

	start = get_current_time();
	while (!philo_has_died(philo))
	{
		now = get_current_time();
		if ((now - start) >= time_in_ms)
			break ;
		usleep(500);
	}
}

void	print_log(t_philo *philo, char *status)
{
	long		timestamp;

	pthread_mutex_lock(&philo->sim->write_lock);
	if (philo_has_died(philo))
	{
		pthread_mutex_unlock(&philo->sim->write_lock);
		return ;
	}
	timestamp = get_current_time() - philo->sim->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->sim->write_lock);
}

int	philo_has_died(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->sim->dead_lock);
	result = philo->sim->died;
	pthread_mutex_unlock(&philo->sim->dead_lock);
	return (result);
}
