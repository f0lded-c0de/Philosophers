/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsamzun <bsamzun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:24:27 by bsamzun           #+#    #+#             */
/*   Updated: 2025/10/14 19:26:46 by bsamzun          ###   ########.fr       */
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
	/* pthread_mutex_t launch_lock; */
	int				stop;
	pthread_t		charon_tid;
	int				c_tid_init;
	pthread_mutex_t	stop_lock;
	int				count;
	pthread_mutex_t	count_lock;
	long unsigned	start;
	pthread_mutex_t	printf_lock;
}		t_data;

typedef struct s_philo
{
	t_data			*data;
	int				seat;
	int				ded;
	pthread_mutex_t	ded_lock;
	pthread_t		tid;
	int				tid_init;
	long unsigned	last_meal;
	pthread_mutex_t	last_lock;
	int				meal_count;
	t_philo			*next;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	int				mutex_init;
}					t_philo;

/* * * * * * * * * * * * * * * * * Functions  * * * * * * * * * * * * * * * * */
// core/philo.c
t_philo			*philo_new(t_data *data, pthread_mutex_t *left, int seat);
void			philo_free(t_philo *head);
void			update_last_meal(t_philo *philo);
int				am_i_dead(t_philo *philo);

// core/philo_routine.c
void			*philo_routine(void *data);
void			philo_death(t_philo *philo);

// core/parsing.c
int				parse_args(t_data *data, char **av, int ac);

// core/charon_routine.c
void			*charon_routine(void *arg);

// utils/utils.c
int				stopped(t_data *data);
int				disp_msg(t_philo *philo, char *message);
void			unlock_both(pthread_mutex_t *left, pthread_mutex_t *right);

// utils/time.c
long unsigned	get_true_time(void);
long unsigned	get_sim_time(t_data *data);
int				sleep_for(t_philo *philo, long unsigned ms);
void			wait_for(long unsigned ms);

// utils/str.c
int				ft_strlen(const char *str);
int				ft_atoi(const char *nptr);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

/* * * * * * * * * * * * * * * * * * Macros * * * * * * * * * * * * * * * * * */
// Philo Messages
# define FRK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define EEP_MSG "is sleeping"
# define THK_MSG "is thinking"
# define DED_MSG "is dead"

#endif
