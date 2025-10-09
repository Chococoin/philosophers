/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:25:45 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/09/23 21:27:14 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_config(t_config *config, char **argv)
{
	int	i;

	config->num_of_philosophers = ft_atoi(argv[1]);
	config->time_to_die = ft_atoi(argv[2]);
	config->time_to_eat = ft_atoi(argv[3]);
	config->time_to_sleep = ft_atoi(argv[4]);
	config->num_complete_meals = 0;
	config->ok = 1;
	config->min_num_of_meals = 0;
	if (argv[5])
		config->min_num_of_meals = ft_atoi(argv[5]);
	i = 0;
	while (i < config->num_of_philosophers)
	{
		pthread_mutex_init(&config->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&config->print_lock, NULL);
	pthread_mutex_init(&config->meals_lock, NULL);
	pthread_mutex_init(&config->state_lock, NULL);
}

void	print_action(t_philo *philo, char *action)
{
	double	timestamp;

	pthread_mutex_lock(&philo->config->print_lock);
	timestamp = chrono_lap(&philo->config->t);
	printf("%.3f %d %s\n", timestamp, philo->id, action);
	pthread_mutex_unlock(&philo->config->print_lock);
}
