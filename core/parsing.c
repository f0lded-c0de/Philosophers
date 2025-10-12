/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsamzun <bsamzun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:35:37 by bsamzun           #+#    #+#             */
/*   Updated: 2025/10/12 12:49:42 by bsamzun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_only_digits(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		if (av[i][j] == '-')
			return (puterr(NEG_ERR), 0);
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (puterr(NON_DIG), 0);
			j++;
		}
		i++;
	}
	return (1);
}

int	parse_args(t_data *data, char **av, int ac)
{
	if (!is_only_digits(av))
		return (0);
	data->num = ft_atoi(av[1]);
	data->ded = ft_atoi(av[2]);
	data->eat = ft_atoi(av[3]);
	data->eep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->min = ft_atoi(av[5]);
		data->count = 0;
		if (!pthread_mutex_init(&data->count_lock, NULL))
			return (puterr(MUT_ERR), 0);
	}
	else
		data->min = -1;
	data->stop = 0;
	if (data->num == -1 || data->ded == -1 || data->eat == -1
		|| data->eep == -1 || (ac == 6 && data->min == -1))
		return (0);
	return (1);
}
