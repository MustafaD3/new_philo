/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 03:42:45 by mdalkili          #+#    #+#             */
/*   Updated: 2025/10/31 04:44:27 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_philo_status(t_philo *philo, char *str)
{
	long		timestamp;

	pthread_mutex_lock(&philo->monitor->write_lock);
	if (is_philo_dead(philo))
	{
		pthread_mutex_unlock(&philo->monitor->write_lock);
		return ;
	}
	timestamp = get_current_time() - philo->monitor->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, str);
	pthread_mutex_unlock(&philo->monitor->write_lock);
}
