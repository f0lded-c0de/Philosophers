/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charon_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsamzun <bsamzun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 19:18:18 by bsamzun           #+#    #+#             */
/*   Updated: 2025/10/14 19:20:56 by bsamzun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cross_styx(t_philo *philo)
{
	pthread_mutex_lock(&philo->ded_lock);
	if (!philo->ded)
	{
		philo->ded = 1;
		if (disp_msg(philo, DED_MSG))
		{
			pthread_mutex_lock(&philo->data->stop_lock);
			philo->data->stop = 1;
			pthread_mutex_unlock(&philo->data->stop_lock);
		}
	}
	pthread_mutex_unlock(&philo->ded_lock);
}

void	*charon_routine(void *arg)
{
	t_philo	*table;
	t_philo	*philo;
	t_data	*data;

	table = (t_philo *)arg;
	data = table->data;
	while (get_true_time() < data->start)
		usleep(50);
	while (!stopped(data))
	{
		philo = table;
		while (philo)
		{
			if (am_i_dead(philo))
				cross_styx(philo);
			philo = philo->next;
		}
	}
	return (NULL);
}
