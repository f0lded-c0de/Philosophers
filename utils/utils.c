/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsamzun <bsamzun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:57:19 by bsamzun           #+#    #+#             */
/*   Updated: 2025/10/09 19:01:34 by bsamzun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long unsigned	get_true_time(t_data *data)
{
	long unsigned	time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time - data->start);
}

void	disp_msg(t_philo *philo, char *message)
{
	printf("%lu %d %s\n", get_true_time(philo->data), philo->seat, message);
}

void	wait_for(long unsigned ms, t_data *data)
{
	long unsigned	start;

	start = get_true_time(data);
	while (start + ms > get_true_time(data))
		continue ;
}

void	unlock_both(pthread_mutex_t *left, pthread_mutex_t *right)
{
	pthread_mutex_unlock(right);
	pthread_mutex_unlock(left);
}
