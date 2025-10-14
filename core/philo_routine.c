/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsamzun <bsamzun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 12:35:01 by bsamzun           #+#    #+#             */
/*   Updated: 2025/10/12 16:12:57 by bsamzun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->ded_lock);
	if (!philo->ded)
	{
		philo->ded = 1;
		pthread_mutex_unlock(&philo->ded_lock);
		if (disp_msg(philo, DED_MSG))
		{
			pthread_mutex_lock(&philo->data->stop_lock);
			philo->data->stop = 1;
			pthread_mutex_unlock(&philo->data->stop_lock);
		}
	}
	else
		pthread_mutex_unlock(&philo->ded_lock);
}

void	philo_upcheck_count(t_philo *philo)
{
	philo->meal_count++;
	if (philo->data->min > -1)
	{
		if (philo->meal_count == philo->data->min)
		{
			pthread_mutex_lock(&philo->data->count_lock);
			philo->data->count++;
			pthread_mutex_unlock(&philo->data->count_lock);
		}
		if (philo->data->count == philo->data->num)
		{
			pthread_mutex_lock(&philo->data->stop_lock);
			philo->data->stop = 1;
			pthread_mutex_unlock(&philo->data->stop_lock);
		}
	}
}

int	metro_boulot_dodo(t_philo *philo)
{
	if (stopped(philo->data))
		return (0);
	if (!disp_msg(philo, THK_MSG))
		return (0);
	pthread_mutex_lock(philo->right);
	if (!disp_msg(philo, FRK_MSG))
		return (pthread_mutex_unlock(philo->right), 0);
	if (am_i_dead(philo))
		return (philo_death(philo), pthread_mutex_unlock(philo->right), 0);
	pthread_mutex_lock(philo->left);
	if (!disp_msg(philo, FRK_MSG))
		return (unlock_both(philo->left, philo->right), 0);
	if (am_i_dead(philo))
		return (philo_death(philo), unlock_both(philo->left, philo->right), 0);
	if (!disp_msg(philo, EAT_MSG))
		return (unlock_both(philo->left, philo->right), 0);
	update_last_meal(philo);
	if (!sleep_for(philo, philo->data->eat))
		return (0);
	unlock_both(philo->left, philo->right);
	philo_upcheck_count(philo);
	if (!disp_msg(philo, EEP_MSG) || !sleep_for(philo, philo->data->eep))
		return (0);
	return (1);
}

void	*solo_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	disp_msg(philo, FRK_MSG);
	wait_for(philo->data->ded);
	disp_msg(philo, DED_MSG);
	pthread_mutex_unlock(philo->right);
	return (NULL);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (!philo->data->min)
		return (NULL);
	while (get_true_time() < philo->data->start)
		usleep(50);
	pthread_mutex_lock(&philo->last_lock);
	philo->last_meal = philo->data->start;
	pthread_mutex_unlock(&philo->last_lock);
	if (philo->data->ded == 0)
		return (NULL);
	if (philo->data->num == 1)
		return (solo_philo(philo));
	if (philo->seat % 2)
		wait_for(philo->data->eat / 2);
	while (metro_boulot_dodo(philo))
		continue ;
	return (NULL);
}
