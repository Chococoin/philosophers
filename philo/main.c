/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:28:08 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/09/19 12:54:38 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "philo.h"

void	print_action(t_philo *philo, char *action)
{
	double	timestamp;

	pthread_mutex_lock(&philo->config->print_lock);
	timestamp = chrono_lap(&philo->config->t);
	printf("%.3f %d %s\n", timestamp, philo->id, action);
	pthread_mutex_unlock(&philo->config->print_lock);
}

void	init_config(t_config *config, char **argv)
{
	int	i;

	config->num_of_philosophers = ft_atoi(argv[1]);
	config->time_to_die = ft_atoi(argv[2]);
	config->time_to_eat = ft_atoi(argv[3]);
	config->time_to_sleep = ft_atoi(argv[4]);
	config->ok = 1;
	if (argv[5])
		config->min_num_of_meals = ft_atoi(argv[5]);
	i = 0;
	while (i < config->num_of_philosophers)
	{
		pthread_mutex_init(&config->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&config->print_lock, NULL);
}

void	*philosophers_life(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (philo->config->ok)
	{
		if (try_eat(philo))
		{
			usleep(philo->config->time_to_eat * 1000);
			print_action(philo, "is sleeping");
			usleep(philo->config->time_to_sleep * 1000);
			print_action(philo, "is thinking");
		}
		else
			usleep(100);
	}
	pthread_mutex_lock(&philo->config->forks[philo->right_fork]);
	return (NULL);
}

void	init_philosophers(t_config *config, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < config->num_of_philosophers)
	{
		philo[i].id = i + 1;
		philo[i].config = config;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % config->num_of_philosophers;
		philo[i].last_meal = chrono_lap(&config->t);
		pthread_create(&philo[i].thread, NULL, philosophers_life, &philo[i]);
		i++;
	}
	return ;
}

void	start_dinner(t_config *config, t_philo *philo)
{
	int	i;

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
	chrono_stop(&config.t);
	// free(config.t);
}

/* int	main(int argc, char **argv)
{
	cleanup_and_exit();           // Libera recursos
	return (0);
} */
