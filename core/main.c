/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsamzun <bsamzun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:21:27 by bsamzun           #+#    #+#             */
/*   Updated: 2025/10/12 13:38:29 by bsamzun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	swap_forks(t_philo *head)
{
	pthread_mutex_t	*tmp;

	while (head)
	{
		if (head->seat % 2 == 0)
		{
			tmp = head->right;
			head->right = head->left;
			head->left = tmp;
		}
		head = head->next;
	}
}

static t_philo	*set_table(t_data *data)
{
	t_philo	*head;
	t_philo	*tmp;
	int		i;

	i = 1;
	head = philo_new(data, NULL, i);
	if (!head)
		return (NULL);
	tmp = head;
	while (i < data->num)
	{
		tmp->next = philo_new(data, tmp->right, i + 1);
		if (!tmp->next)
			return (philo_free(head), NULL);
		tmp = tmp->next;
		i++;
	}
	head->left = tmp->right;
	swap_forks(head);
	return (head);
}

void	launch_sim(t_philo *table)
{
	t_philo	*philo;

	philo = table;
	table->data->start = 0;
	table->data->start = get_true_time() + (table->data->num * 5);
	while (philo)
	{
		if (pthread_create(&philo->tid, NULL, philo_routine, philo))
			return (puterr(THR_ERR), philo_free(table));
		philo->tid_init = 1;
		philo = philo->next;
	}
	philo = table;
	while (philo)
	{
		pthread_join(philo->tid, NULL);
		philo->tid_init = 0;
		philo = philo->next;
	}
	pthread_mutex_destroy(&table->data->stop_lock);
	pthread_mutex_destroy(&table->data->printf_lock);
	if (table->data->min > -1)
		pthread_mutex_destroy(&table->data->count_lock);
	philo_free(table);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*table;

	if (ac < 5)
		return (puterr(MIN_ARG), 1);
	if (ac > 6)
		return (puterr(MAX_ARG), 1);
	if (!parse_args(&data, av, ac))
		return (1);
	table = set_table(&data);
	if (!table)
		return (1);
	launch_sim(table);
	return (0);
}
