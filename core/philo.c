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

t_philo	*philo_new(t_data *data, pthread_mutex_t *left, int seat)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (puterr(MLC_ERR), NULL);
	new->right = malloc(sizeof(pthread_mutex_t));
	if (!new->right)
		return (puterr(MLC_ERR), free(new), NULL);
	new->right_init = 0;
	if (pthread_mutex_init(new->right, NULL))
		return (puterr(MUT_ERR), free(new->right), free(new), NULL);
	new->right_init = 1;
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
	t_philo	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->tid_init)
			pthread_join(head->tid, NULL);
		if (head->seat % 2 && head->right)
		{
			if (head->right_init)
				pthread_mutex_destroy(head->right);
			free(head->right);
		}
		if (head->seat % 2 == 0 && head->left)
		{
			if (head->right_init)
				pthread_mutex_destroy(head->left);
			free(head->left);
		}
		free(head);
		head = tmp;
	}
}
