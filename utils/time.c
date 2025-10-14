/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsamzun <bsamzun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 15:57:40 by bsamzun           #+#    #+#             */
/*   Updated: 2025/10/12 16:14:08 by bsamzun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long unsigned	get_true_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long unsigned	get_sim_time(t_data *data)
{
	long unsigned	time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time - data->start);
}

int	sleep_for(t_philo *philo, long unsigned ms)
{
	long unsigned	start;

	start = get_true_time();
	while (start + ms > get_true_time())
	{
		usleep(50);
		pthread_mutex_lock(&philo->last_lock);
		if (get_true_time() > (philo->last_meal + philo->data->ded))
			return (pthread_mutex_unlock(&philo->last_lock),
				philo_death(philo), 0);
		pthread_mutex_unlock(&philo->last_lock);
	}
	return (1);
}

void	wait_for(long unsigned ms)
{
	long unsigned	start;

	start = get_true_time();
	while (start + ms > get_true_time())
		usleep(50);
}
