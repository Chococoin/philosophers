/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:28:08 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/09/16 15:25:38 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_config(t_config *config, char **argv)
{
	config->num_of_philosophers = ft_atoi(argv[1]);
	config->time_to_die = ft_atoi(argv[2]);
	config->time_to_eat = ft_atoi(argv[3]);
	config->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		config->min_num_of_meals = ft_atoi(argv[5]);
}

void	*philosophers_life(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	printf("Soy el filósofo %d\n", philo->id);
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
		pthread_create(&philo[i].thread, NULL, philosophers_life, &philo[i]);
		i++;
	}
	return ;
}

void	start_dinner(t_config *config, t_philo *philo)
{
	int	i;

	i = 0;
	config->ok = 1;
	while (i < config->num_of_philosophers - 1)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	config->t = chrono_start();
	return ;
}

int	main(int argc, char **argv)
{
	double		time_lap;
	t_config	config;
	t_philo		philosopher[200];

	if (!valid_args(argc, argv))
		return (1);
	init_config(&config, argv);
	init_philosophers(&config, philosopher);
	start_dinner(&config, philosopher);
	printf("Time lap: %f\n", time_lap);
	chrono_stop(config.t);
}

/* int	main(int argc, char **argv)
{
	start_simulation();           // Controla el tiempo y acciones
	cleanup_and_exit();           // Libera recursos
	return (0);
} */
