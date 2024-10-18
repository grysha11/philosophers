/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:14:43 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/17 17:55:25 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


void	try_to_eat(t_philo *philo)
{
	
}

void	print_information(t_philo *philo, int type)
{
	
}

void	routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->stop);
		if (exit == 1)
		{
			pthread_mutex_undlock(&philo->data->stop);
			break;
		}
		pthread_mutex_unlock(&philo->data->stop);
		try_to_eat()
	}
}

int	init_loop(t_data *data)
{
	pthread_t	philo_threads[data->amount];
	t_philo		philos[data->amount];
	int			i;

	pthread_mutex_init(&data->stop, NULL);
	pthread_mutex_init(&data->print, NULL);

	i = 0;
	while (i < data->amount)
	{
		philos[i].id = i;
		philos[i].state = THINK;
		philos[i].dead = 0;
		philos[i].data = &data;
		if (pthread_create(&philo_threads[i], NULL, routine, (void *)&philos[i]) != 0)
		{
			perror("Failed to create thread");
			return (FALSE);
		}
		i++;
	}

	i = 0;
	while (i < data->amount)
	{
		pthread_join(philo_threads[i], NULL);
		i++;
	}
	
	pthread_mutex_destroy(&data->stop);
	pthread_mutex_destroy(&data->print);
	return (TRUE);
}
