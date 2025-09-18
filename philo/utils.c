/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:10:08 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/09/18 14:12:25 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}

t_timeval	chrono_start(void)
{
	t_timeval	t;
	gettimeofday(&t.start, NULL);
	return (t);
}

double	chrono_lap(t_timeval *t)
{
	long	secs;
	long	microsecs;
	double	time_lap;

	gettimeofday(&t->end, NULL);
	secs = t->end.tv_sec - t->start.tv_sec;
	microsecs = t->end.tv_usec - t->start.tv_usec;
	if (microsecs < 0)
	{
		secs -= 1;
		microsecs += 1000000;
	}
	time_lap = secs + microsecs * 1e-6;
	return (time_lap);
}

void	chrono_stop(t_timeval *t)
{
	long	secs;
	long	microsecs;
	double	total_time;

	gettimeofday(&t->end, NULL);
	secs = t->end.tv_sec - t->start.tv_sec;
	microsecs = t->end.tv_usec - t->start.tv_usec;
	if (microsecs < 0)
	{
		secs -= 1;
		microsecs += 1000000;
	}
	total_time = secs + microsecs * 1e-6;
	printf("Tiempo de ejecución: %f segundos\n", total_time);
}

int	valid_args(int argc, char **argv)
{
	int	n_phils;

	if (argc && argc < 5)
	{
		printf("Usage: ./philo n_phils t_2_die t_2_eat t_2_sleep [n_meals]\n");
		return (0);
	}
	n_phils = ft_atoi(argv[1]);
	if (n_phils < 1 || n_phils > 200)
	{
		printf("Number of philosophers must be in a range of 1-200\n");
		return (0);
	}
	return (1);
}
int	try_eat(t_philo *philo)
{
	if (pthread_mutex_trylock(&philo->config->forks[philo->left_fork]) == 0)
	{
		printf("%d has taken a fork\n", philo->id);
		if (pthread_mutex_trylock(&philo->config->forks[philo->right_fork]) == 0)
		{
			printf("%d has taken a fork\n", philo->id);
			pthread_mutex_unlock(&philo->config->forks[philo->right_fork]);
			pthread_mutex_unlock(&philo->config->forks[philo->left_fork]);
			return (1);
		}
		else
			pthread_mutex_unlock(&philo->config->forks[philo->left_fork]);
	}
	return (0);
}
