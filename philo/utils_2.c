/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:11:14 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/09/23 21:36:38 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lock_forks_and_count(t_philo *philo, int first, int second)
{
	if (pthread_mutex_trylock(&philo->config->forks[first]) != 0)
		return (0);
	print_action(philo, "has taken a fork");
	if (pthread_mutex_trylock(&philo->config->forks[second]) != 0)
	{
		pthread_mutex_unlock(&philo->config->forks[first]);
		return (0);
	}
	print_action(philo, "has taken a fork");
	philo->eaten_meals++;
	pthread_mutex_unlock(&philo->config->forks[second]);
	pthread_mutex_unlock(&philo->config->forks[first]);
	return (1);
}

int	try_eat(t_philo *philo)
{
	int	first;
	int	second;

	if (!is_alive(philo))
	{
		philo->config->ok = 0;
		return (0);
	}
	select_forks(philo, &first, &second);
	return (lock_forks_and_count(philo, first, second));
}

int	is_alive(t_philo *philo)
{
	double	now;

	now = chrono_lap(&philo->config->t);
	if (now - philo->last_meal > philo->config->time_to_die)
	{
		print_action(philo, "died");
		philo->config->ok = 0;
		return (0);
	}
	return (1);
}

int	are_meals_complete(t_philo *philo)
{
	int	all_satiated;
	int	n_compl_meals;
	int	n_philo;

	n_compl_meals = philo->config->num_complete_meals;
	n_philo = philo->config->num_of_philosophers;
	if (philo->config->min_num_of_meals == 0)
		return (0);
	pthread_mutex_lock(&philo->config->meals_lock);
	if (!philo->finished_meals
		&& philo->eaten_meals >= philo->config->min_num_of_meals)
	{
		philo->finished_meals = 1;
		philo->config->num_complete_meals++;
	}
	all_satiated = (n_compl_meals == n_philo);
	pthread_mutex_unlock(&philo->config->meals_lock);
	return (all_satiated);
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
