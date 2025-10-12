/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsamzun <bsamzun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:24:26 by bsamzun           #+#    #+#             */
/*   Updated: 2025/10/12 13:03:48 by bsamzun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

/* * * * * * * * * * * * * * * * * Functions  * * * * * * * * * * * * * * * * */
// errors.c
void	puterr(char *error);

/* * * * * * * * * * * * * * * * * * Macros * * * * * * * * * * * * * * * * * */
# define MIN_ARG "philo: Minimum 4 argument"
# define MAX_ARG "philo: Maximum 5 argument"
# define NEG_ERR "philo: No negative value accepted"
# define NON_DIG "philo: Arguments have to be stricly numerical"
# define INT_ERR "philo: No number greater than int max accepted"
# define MLC_ERR "philo: Malloc failed"
# define MUT_ERR "philo: Mutex failed"
# define THR_ERR "philo: Thread failed"

#endif
