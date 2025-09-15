/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:28:08 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/09/15 20:37:41 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


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
