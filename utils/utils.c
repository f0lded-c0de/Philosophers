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

int	stopped(t_data *data)
{
	int	ret;

	pthread_mutex_lock(&data->stop_lock);
	if (data->stop)
		ret = 1;
	else
		ret = 0;
	pthread_mutex_unlock(&data->stop_lock);
	return (ret);
}

int	disp_msg(t_philo *philo, char *message)
{
	long unsigned	time_to_wait;

	pthread_mutex_lock(&philo->data->printf_lock);
	pthread_mutex_lock(&philo->data->stop_lock);
	if (philo->data->stop)
		return (pthread_mutex_unlock(&philo->data->stop_lock),
			pthread_mutex_unlock(&philo->data->printf_lock), 0);
	pthread_mutex_unlock(&philo->data->stop_lock);
	printf("%lu %d %s\n", get_sim_time(philo->data), philo->seat, message);
	pthread_mutex_unlock(&philo->data->printf_lock);
	if (!ft_strncmp(THK_MSG, message, ft_strlen(THK_MSG) + 1)
		&& philo->meal_count >= 1)
	{
		time_to_wait = philo->data->ded - (get_true_time() - philo->last_meal);
		time_to_wait -= (philo->data->eat / 2);
		sleep_for(philo, time_to_wait);
	}
	return (1);
}

void	unlock_both(pthread_mutex_t *left, pthread_mutex_t *right)
{
	pthread_mutex_unlock(left);
	pthread_mutex_unlock(right);
}
