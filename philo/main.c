/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:28:08 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/09/08 17:42:36 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_timeval	*chrono_start(void)
{
	t_timeval *new_t = malloc(sizeof(t_timeval));
	new_t->start = malloc(sizeof(struct timeval));
	new_t->end = malloc(sizeof(struct timeval));
	if (!new_t->start || !new_t->end)
		exit(1);
	gettimeofday(new_t->start, NULL);
	return (new_t);
}

double chrono_lap(t_timeval *t)
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

void chrono_stop(t_timeval *t)
{
	gettimeofday(t->end, NULL);
	long secs = t->end->tv_sec - t->start->tv_sec;
	long microsecs = t->end->tv_usec - t->start->tv_usec;
	if (microsecs < 0)
	{
		secs -= 1;
		microsecs += 1000000;
	}
	double total_time = secs + microsecs * 1e-6;
	printf("Tiempo de ejecución: %f segundos\n", total_time);
	printf("Micro: %ld\n", microsecs);
	printf("Secs: %ld\n", secs);
	free(t->end);
	free(t->start);
	free(t);
}

int	main(int argc, char **argv)
{
	t_timeval	*t;
	double		time_lap;
	(void)argv;
	if (argc != 5)
	{
		printf("Error\n");
		exit(1);
	}
	t = chrono_start();
	for (int i = 0; i <= 100; i++)
	{
		printf("Hola %d\n", i);
	}
	time_lap = chrono_lap(t);
	printf("Time lap: %f\n", time_lap);
	for (int i = 100; i <= 200; i++)
	{
		printf("Hola %d\n", i);
	}
	chrono_stop(t);
}
