/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsamzun <bsamzun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 12:35:01 by bsamzun           #+#    #+#             */
/*   Updated: 2025/10/12 12:54:43 by bsamzun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_death(t_philo *philo)
{
	disp_msg(philo, DED_MSG);
	philo->data->stop = 1;
}

void	philo_upcheck_count(t_philo *philo)
{
	philo->meal_count++;
	if (philo->meal_count == philo->data->min)
	{
		pthread_mutex_lock(&philo->data->count_lock);
		philo->data->count++;
		pthread_mutex_unlock(&philo->data->count_lock);
	}
	if (philo->data->count == philo->data->num)
		philo->data->stop = 1;
}

int	metro_boulot_dodo(t_philo *philo)
{
	disp_msg(philo, THK_MSG);
	pthread_mutex_lock(philo->right);
	if (philo->data->stop)
		return (pthread_mutex_unlock(philo->right), 0);
	disp_msg(philo, FRK_MSG);
	if (get_true_time() > (philo->last_meal + philo->data->ded))
		return (philo_death(philo), pthread_mutex_unlock(philo->right), 0);
	pthread_mutex_lock(philo->left);
	if (philo->data->stop)
		return (unlock_both(philo->left, philo->right), 0);
	disp_msg(philo, FRK_MSG);
	if (get_true_time() > (philo->last_meal + philo->data->ded))
		return (philo_death(philo), unlock_both(philo->left, philo->right), 0);
	disp_msg(philo, EAT_MSG);
	philo->last_meal = get_true_time();
	wait_for(philo->data->eat);
	unlock_both(philo->left, philo->right);
	if (philo->data->min > -1)
		philo_upcheck_count(philo);
	if (philo->data->stop)
		return (0);
	disp_msg(philo, EEP_MSG);
	wait_for(philo->data->eep);
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
	philo->last_meal = philo->data->start;
	if (philo->data->ded == 0)
		return (NULL);
	if (philo->data->num == 1)
		return (solo_philo(philo));
	while (!philo->data->stop && metro_boulot_dodo(philo))
		continue ;
	return (NULL);
}
