/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsamzun <bsamzun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:24:27 by bsamzun           #+#    #+#             */
/*   Updated: 2025/10/12 13:04:39 by bsamzun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* * * * * * * * * * * * * * * * * Includes * * * * * * * * * * * * * * * * * */
// system
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

// custom
# include "errors.h"

/* * * * * * * * * * * * * * * * * Structures * * * * * * * * * * * * * * * * */
// struct prototypes
typedef struct s_philo	t_philo;

// struct
typedef struct s_data
{
	int				num;
	int				ded;
	int				eat;
	int				eep;
	int				min;
	int				stop;
	int				count;
	pthread_mutex_t	count_lock;
	long unsigned	start;
}		t_data;

typedef struct s_philo
{
	t_data			*data;
	int				seat;
	int				ded;
	pthread_t		tid;
	int				tid_init;
	long unsigned	last_meal;
	int				meal_count;
	t_philo			*next;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	int				right_init;
}					t_philo;

/* * * * * * * * * * * * * * * * * Functions  * * * * * * * * * * * * * * * * */
// core/philo.c
t_philo			*philo_new(t_data *data, pthread_mutex_t *left, int seat);
void			philo_free(t_philo *head);

// core/philo_routine.c
void			*philo_routine(void *data);

// core/parsing.c
int				parse_args(t_data *data, char **av, int ac);

// utils/utils.c
long unsigned	get_true_time(t_data *data);
void			disp_msg(t_philo *philo, char *message);
void			wait_for(long unsigned ms, t_data *data);
void			unlock_both(pthread_mutex_t *left, pthread_mutex_t *right);

// utils/str.c
int				ft_strlen(const char *str);
int				ft_atoi(const char *nptr);

/* * * * * * * * * * * * * * * * * * Macros * * * * * * * * * * * * * * * * * */
// Philo Messages
# define FRK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define EEP_MSG "went to sleep"
# define THK_MSG "is thinking"
# define DED_MSG "is dead"

#endif
