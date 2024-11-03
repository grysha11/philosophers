/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:18:39 by hzakharc          #+#    #+#             */
/*   Updated: 2024/11/03 14:17:45 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->amount)
	{
		if (pthread_create(&data->philos[i].thrd, NULL, routine,
				(void *)&data->philos[i]) != 0)
			return (false);
		usleep(100);
		i++;
	}
	return (true);
}

bool	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->amount)
	{
		if (pthread_join(data->philos[i].thrd, NULL) != 0)
			return (false);
		i++;
	}
	return (true);
}

void	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->stop, NULL);
	pthread_mutex_init(&data->end_c, NULL);
	pthread_mutex_init(&data->print, NULL);
	while (i < data->amount)
	{
		data->forks[i].taken = false;
		data->forks[i].id = i;
		if ((i + 1) % 2 == 0)
			data->forks[i].last = (i + 1) % data->amount;
		else
			data->forks[i].last = -1;
		pthread_mutex_init(&data->forks[i].mutex, NULL);
		i++;
	}
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->amount)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_c = 0;
		data->philos[i].state = THINK;
		data->philos[i].data = data;
		data->philos[i].fork_r = &data->forks[i];
		data->philos[i].start_t = get_time();
		data->philos[i].time_e = data->philos[i].start_t;
		data->philos[i].fork_l = &data->forks[(i + 1) % data->amount];
		i++;
	}
}

void	initialize(t_data *data)
{
	init_mutexes(data);
	init_philos(data);
	if (!create_threads(data))
	{
		printf("error during initializing threads\n");
		return ;
	}
	if (!join_threads(data))
	{
		printf("error during joining threads\n");
		return ;
	}
}
