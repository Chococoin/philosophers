/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:28:08 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/09/15 19:57:24 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_timeval	*chrono_start(void)
{
	t_timeval	*new_t;

	new_t = malloc(sizeof(t_timeval));
	if (!new_t)
		return (1);
	new_t->start = malloc(sizeof(struct timeval));
	new_t->end = malloc(sizeof(struct timeval));
	if (!new_t->start || !new_t->end)
		exit(1);
	gettimeofday(new_t->start, NULL);
	return (new_t);
}

double	chrono_lap(t_timeval *t)
{
	long	secs;
	long	microsecs;
	double	time_lap;

	gettimeofday(t->end, NULL);
	secs = t->end->tv_sec - t->start->tv_sec;
	microsecs = t->end->tv_usec - t->start->tv_usec;
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

	gettimeofday(t->end, NULL);
	secs = t->end->tv_sec - t->start->tv_sec;
	microsecs = t->end->tv_usec - t->start->tv_usec;
	if (microsecs < 0)
	{
		secs -= 1;
		microsecs += 1000000;
	}
	total_time = secs + microsecs * 1e-6;
	printf("Tiempo de ejecución: %f segundos\n", total_time);
	printf("Micro: %ld\n", microsecs);
	printf("Secs: %ld\n", secs);
	free(t->end);
	free(t->start);
	free(t);
}

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

int	main(int argc, char **argv)
{
	t_timeval	*t;
	double		time_lap;

	if (!valid_args(argc, argv))
		return (1);
	t = chrono_start();
	time_lap = chrono_lap(t);
	printf("Time lap: %f\n", time_lap);
	chrono_stop(t);
}

/* int	main(int argc, char **argv)
{
	if (!valid_args(argc, argv))
		return (1);
	init_config(argv);             // Inicializa structs, mutex, etc.
	init_philosophers();          // Crea y lanza los hilos
	start_simulation();           // Controla el tiempo y acciones
	cleanup_and_exit();           // Libera recursos
	return (0);
} */
