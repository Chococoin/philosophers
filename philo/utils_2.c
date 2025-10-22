/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:11:14 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/10/22 14:03:24 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	select_forks(t_philo *philo, int *first, int *second)
{
	int	left;
	int	right;

	left = philo->left_fork;
	right = philo->right_fork;
	*first = left;
	*second = right;
	if (*first > *second)
	{
		*first = right;
		*second = left;
	}
	return ;
}

int	lock_forks_and_count(t_philo *philo, int first, int second)
{
	if (philo->config->num_of_philosophers == 1)
	{
		if (pthread_mutex_lock(&philo->config->forks[first]) != 0)
			return (0);
		print_action(philo, "has taken a fork");
		usleep(philo->config->time_to_die * 1000);
		pthread_mutex_unlock(&philo->config->forks[first]);
		return (0);
	}
	if (pthread_mutex_lock(&philo->config->forks[first]) != 0)
		return (0);
	print_action(philo, "has taken a fork");
	if (pthread_mutex_lock(&philo->config->forks[second]) != 0)
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

int	is_alive(t_philo *philo)
{
	double	now;
	int		should_report;

	now = chrono_lap(&philo->config->t);
	if (now - philo->last_meal > philo->config->time_to_die)
	{
		should_report = 0;
		pthread_mutex_lock(&philo->config->state_lock);
		if (philo->config->ok)
		{
			philo->config->ok = 0;
			should_report = 1;
		}
		pthread_mutex_unlock(&philo->config->state_lock);
		if (should_report)
			print_action(philo, "died");
		return (0);
	}
	return (1);
}

int	try_eat(t_philo *philo)
{
	int	first;
	int	second;
	int	should_eat;
	int	sim_running;

	pthread_mutex_lock(&philo->config->meals_lock);
	should_eat = !philo->finished_meals;
	pthread_mutex_unlock(&philo->config->meals_lock);
	if (!should_eat)
		return (0);
	pthread_mutex_lock(&philo->config->state_lock);
	sim_running = philo->config->ok;
	pthread_mutex_unlock(&philo->config->state_lock);
	if (!sim_running)
		return (0);
	select_forks(philo, &first, &second);
	return (lock_forks_and_count(philo, first, second));
}

int	are_meals_complete(t_philo *philo)
{
	int	all_satiated;
	int	n_compl_meals;
	int	n_philo;

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
	n_compl_meals = philo->config->num_complete_meals;
	all_satiated = (n_compl_meals == n_philo);
	pthread_mutex_unlock(&philo->config->meals_lock);
	return (all_satiated);
}
