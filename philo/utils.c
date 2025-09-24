/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:10:08 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/09/24 14:37:00 by glugo-mu         ###   ########.fr       */
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
	struct timeval	now;
	double			ms;

	gettimeofday(&now, NULL);
	ms = (now.tv_sec - t->start.tv_sec) * 1000.0;
	ms += (now.tv_usec - t->start.tv_usec) / 1000.0;
	return (ms);
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
	if (n_phils <= 1 || n_phils > 200)
	{
		printf("Number of philosophers must be in a range of 2-200\n");
		return (0);
	}
	return (1);
}

void	cleanup_and_exit(t_config *c)
{
	int	i;

	i = 0;
	while (i < c->num_of_philosophers)
	{
		pthread_mutex_destroy(&c->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&c->print_lock);
	pthread_mutex_destroy(&c->meals_lock);
	return ;
}
