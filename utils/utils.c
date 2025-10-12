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
	/* long unsigned	time_to_wait; */
	if (philo->data->stop)
		return (0);
	printf("%lu %d %s\n", get_sim_time(philo->data), philo->seat, message);
	/* if (ft_strncmp(THK_MSG, message, ft_strlen(THK_MSG) + 1)) */
	/* { */
	/* 	time_to_wait = philo->data->ded - (get_true_time() - philo->last_meal); */
	/* 	time_to_wait -= (philo->data->eat / 2); */
	/* 	sleep_for(philo, time_to_wait); */
	/* } */
	return (1);
}

void	unlock_both(pthread_mutex_t *left, pthread_mutex_t *right)
{
	pthread_mutex_unlock(left);
	pthread_mutex_unlock(right);
}
