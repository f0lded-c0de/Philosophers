/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsamzun <bsamzun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:33:05 by bsamzun           #+#    #+#             */
/*   Updated: 2025/10/12 12:35:23 by bsamzun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_lock);
	philo->last_meal = get_true_time();
	pthread_mutex_unlock(&philo->last_lock);
}

int	am_i_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->ded_lock);
	if (philo->ded)
		return (pthread_mutex_unlock(&philo->ded_lock), 1);
	pthread_mutex_unlock(&philo->ded_lock);
	pthread_mutex_lock(&philo->last_lock);
	if (get_true_time() > (philo->last_meal + philo->data->ded))
		return (pthread_mutex_unlock(&philo->last_lock), 1);
	pthread_mutex_unlock(&philo->last_lock);
	return (0);
}

int	create_mutex(t_philo *new)
{
	if (pthread_mutex_init(new->right, NULL))
		return (puterr(MUT_ERR), free(new->right), free(new), 0);
	if (pthread_mutex_init(&new->ded_lock, NULL))
		return (puterr(MUT_ERR), pthread_mutex_destroy(new->right),
			free(new->right), free(new), 0);
	if (pthread_mutex_init(&new->last_lock, NULL))
		return (puterr(MUT_ERR), pthread_mutex_destroy(&new->ded_lock),
			pthread_mutex_destroy(new->right), free(new->right),
			free(new), 0);
	return (1);
}

t_philo	*philo_new(t_data *data, pthread_mutex_t *left, int seat)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (puterr(MLC_ERR), NULL);
	new->right = malloc(sizeof(pthread_mutex_t));
	if (!new->right)
		return (puterr(MLC_ERR), free(new), NULL);
	new->mutex_init = 0;
	if (!create_mutex(new))
		return (NULL);
	new->mutex_init = 1;
	new->left = left;
	new->data = data;
	new->seat = seat;
	new->ded = 0;
	new->tid_init = 0;
	new->meal_count = 0;
	new->next = NULL;
	return (new);
}

void	philo_free(t_philo *head)
{
	t_philo			*tmp;
	pthread_mutex_t	*to_rm;

	while (head)
	{
		if (head->seat % 2)
			to_rm = head->right;
		else
			to_rm = head->left;
		tmp = head->next;
		if (head->tid_init)
			pthread_join(head->tid, NULL);
		if (to_rm)
		{
			if (head->mutex_init)
			{
				pthread_mutex_destroy(to_rm);
				pthread_mutex_destroy(&head->ded_lock);
				pthread_mutex_destroy(&head->last_lock);
			}
			free(to_rm);
		}
		free(head);
		head = tmp;
	}
}
