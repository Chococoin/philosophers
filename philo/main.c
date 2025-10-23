/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:28:08 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/10/22 15:36:53 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_routine(t_philo	*philo)
{
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->config->meals_lock);
	philo->last_meal = chrono_lap(&philo->config->t);
	pthread_mutex_unlock(&philo->config->meals_lock);
	usleep(philo->config->time_to_eat * 1000);
	print_action(philo, "is sleeping");
	usleep(philo->config->time_to_sleep * 1000);
	print_action(philo, "is thinking");
	usleep(philo->config->time_to_think * 1000);
	return ;
}

void	*philosophers_life(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		pthread_mutex_lock(&philo->config->state_lock);
		if (!philo->config->ok)
		{
			pthread_mutex_unlock(&philo->config->state_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->config->state_lock);
		if (are_meals_complete(philo))
			break ;
		if (try_eat(philo))
			start_routine(philo);
		else
			usleep(100);
	}
	return (NULL);
}

void	init_philosophers(t_config *config, t_philo *philo)
{
	int	i;

	config->philosophers = philo;
	i = 0;
	while (i < config->num_of_philosophers)
	{
		philo[i].id = i + 1;
		philo[i].config = config;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % config->num_of_philosophers;
		philo[i].last_meal = chrono_lap(&config->t);
		philo[i].eaten_meals = 0;
		philo[i].finished_meals = 0;
		pthread_create(&philo[i].thread, NULL, philosophers_life, &philo[i]);
		i++;
	}
	pthread_create(&config->monitor_thread, NULL, monitor_philosophers, config);
	return ;
}

void	start_dinner(t_config *config, t_philo *philo)
{
	int	i;

	pthread_join(config->monitor_thread, NULL);
	i = 0;
	while (i < config->num_of_philosophers)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return ;
}

int	main(int argc, char **argv)
{
	t_config	config;
	t_philo		philosopher[200];

	if (!valid_args(argc, argv))
		return (1);
	config.t = chrono_start();
	init_config(&config, argv);
	init_philosophers(&config, philosopher);
	start_dinner(&config, philosopher);
	cleanup_and_exit(&config);
	return (0);
}
