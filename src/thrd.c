/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thrd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:05:52 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/28 11:56:18 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	create_thrd(pthread_t *thread, void *routine(void *), void *arg)
{
	if (pthread_create(thread, NULL, routine, arg) != 0)
	{
		printf("Failed to create thread\n");
		return (false);
	}
	return (true);
}

bool	join_thrd(pthread_t *thread)
{
	if (pthread_join(*thread, NULL) != 0)
	{
		printf("Failed to join thread\n");
		return (false);
	}
	return (true);
}

bool	join_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->amount)
	{
		if (!join_thrd(&data->philos[i].thrd))
			return (false);
		i++;
	}
	return (true);
}

bool	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->amount)
	{
		pthread_mutex_lock(&data->stop);
		data->philos[i].id = i + 1;
		data->philos[i].eat_c = 0;
		data->philos[i].state = THINK;
		data->philos[i].dead = false;
		get_forks(&data->philos[i], data->amount);
		data->philos[i].start_t = 0;
		data->philos[i].time = 0;
		data->philos[i].ready = 0;
		data->philos[i].data = data;
		pthread_mutex_unlock(&data->stop);
		if (!create_thrd(&data->philos[i].thrd,
				routine_philo, (void *)&data->philos[i]))
			return (false);
		i++;
	}
	return (true);
}

void	initialize(t_data *data)
{
	pthread_t	monitor;

	init_mutexes(data);
	if (!init_philos(data))
	{
		destroy_mutexes(data);
		return ;
	}
	create_thrd(&monitor, routine_monitor, (void *)data);
	join_thrd(&monitor);
	join_philos(data);
	destroy_mutexes(data);
}
