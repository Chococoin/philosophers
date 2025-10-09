/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:50:21 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/09/23 21:38:15 by glugo-mu         ###   ########.fr       */
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
	int				num_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_num_of_meals;
	int				num_complete_meals;
	int				ok;
	t_timeval		t;
	pthread_mutex_t	forks[200];
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meals_lock;
	pthread_mutex_t	state_lock;
}	t_config;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	int			left_fork;
	int			right_fork;
	int			eaten_meals;
	int			finished_meals;
	double		last_meal;
	t_config	*config;
}	t_philo;

t_timeval	chrono_start(void);
int			ft_atoi(const char *str);
void		init_config(t_config *config, char **argv);
double		chrono_lap(t_timeval *t);
int			valid_args(int argc, char **argv);
int			try_eat(t_philo *philo);
void		print_action(t_philo *philo, char *action);
int			is_alive(t_philo *philo);
int			are_meals_complete(t_philo *philo);
void		cleanup_and_exit(t_config *c);
void		select_forks(t_philo *philo, int *first, int *second);
int			lock_forks_and_count(t_philo *philo, int first, int second);

#endif
