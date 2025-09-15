/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:50:21 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/09/15 20:01:32 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_config
{
	int	*time_to_die;
	int	*time_to_eat;
	int	*time_to_sleep;
}	t_config;

typedef struct s_philo
{
	int			*id;
	pthread_t	thread;
	int			left_fork;
	int			right_fork;
	t_config	*config;
}	t_philo;

typedef struct s_timeval
{
	struct timeval	*start;
	struct timeval	*end;
}	t_timeval;

#endif