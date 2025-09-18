/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:50:21 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/09/18 14:32:15 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_timeval
{
	struct timeval	start;
	struct timeval	end;
}	t_timeval;

typedef struct s_config
{
	int			num_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			min_num_of_meals;
	int			ok;
	t_timeval	t;
	pthread_mutex_t forks[200];
}	t_config;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	int			left_fork;
	int			right_fork;
	int			last_meal;
	t_config	*config;
}	t_philo;

int			ft_atoi(const char *str);
t_timeval	chrono_start(void);
long		chrono_lap(t_timeval *t);
void		chrono_stop(t_timeval *t);
int			valid_args(int argc, char **argv);
int			try_eat(t_philo *philo);
void		print_action(t_philo *philo, char *action);

#endif