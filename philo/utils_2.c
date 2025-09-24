/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:11:14 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/09/24 14:48:31 by glugo-mu         ###   ########.fr       */
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

int	try_eat(t_philo *philo)
{
	int	first;
	int	second;

	if (!is_alive(philo) || philo->finished_meals)
	{
		philo->config->ok = 0;
		return (0);
	}
	select_forks(philo, &first, &second);
	return (lock_forks_and_count(philo, first, second));
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
