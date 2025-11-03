/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalkili <mdalkilic344@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 03:34:50 by mdalkili          #+#    #+#             */
/*   Updated: 2025/11/01 04:15:17 by mdalkili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_all(t_monitor *monitor)
{
	if (monitor->forks)
		free(monitor->forks);
	if (monitor->philos)
		free(monitor->philos);
	return ;
}
