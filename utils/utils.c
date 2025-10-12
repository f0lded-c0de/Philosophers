/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsamzun <bsamzun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:57:19 by bsamzun           #+#    #+#             */
/*   Updated: 2025/10/12 15:58:14 by bsamzun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	disp_msg(t_philo *philo, char *message)
{
	if (philo->data->stop)
		return (0);
	printf("%lu %d %s\n", get_sim_time(philo->data), philo->seat, message);
	return (1);
}

void	unlock_both(pthread_mutex_t *left, pthread_mutex_t *right)
{
	pthread_mutex_unlock(right);
	pthread_mutex_unlock(left);
}
