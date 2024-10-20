/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:17:38 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/20 00:13:30 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine_monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		//add the checkers for death;
	}
}

void	*routine_philo(void *arg)
{

}

bool	create_thrd(pthread_t *thread, void *routine(void *), void *arg)
{
	if (pthread_create(thread, NULL, routine, arg) != 0)
	{
		printf("Failed to create thread\n");
		return (false);
	}
	return (true);
}

bool	join_thrd(pthread_t thread)
{
	if (pthread_join(thread, NULL) != 0)
	{
		printf("Failed to join thread\n");
		return (false);
	}
	return (true);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->amount)
	{
		create_thrd(&data->philos[i].thrd, routine_philo, (void *)data);
		i++;
	}
}

void	initialize(t_data *data)
{
	pthread_t	monitor;

	create_thrd(&monitor, routine_monitor, (void *)data);
	init_philos(data);
	init_mutexes(data);
}
