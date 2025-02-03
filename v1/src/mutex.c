/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:06:03 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/29 09:43:42 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	check_cycles(t_data *data, int i)
{
	pthread_mutex_lock(&data->stop);
	if (data->cycle != -1 && data->philos[i].eat_c >= data->cycle)
	{
		pthread_mutex_unlock(&data->stop);
		return (true);
	}
	pthread_mutex_unlock(&data->stop);
	return (false);
}

bool	routine_monitor_util(t_data **data, int *e_flag, int i)
{
	ssize_t	current_time;

	pthread_mutex_lock(&(*data)->stop);
	current_time = get_time(&(*data)->philos[i]);
	pthread_mutex_unlock(&(*data)->stop);
	if (check_death(data, i))
		return (true);
	if (check_cycles(*data, i))
	{
		pthread_mutex_lock(&(*data)->stop);
		*e_flag = 1;
		pthread_mutex_unlock(&(*data)->stop);
	}
	else
	{
		pthread_mutex_lock(&(*data)->stop);
		*e_flag = 0;
		pthread_mutex_unlock(&(*data)->stop);
	}
	return (false);
}

bool	take_fork(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	if (fork->taken == true && fork->id != philo->id)
	{
		pthread_mutex_unlock(&fork->mutex);
		return (false);
	}
	else
	{
		fork->taken = true;
		fork->id = philo->id;
		pthread_mutex_unlock(&fork->mutex);
		return (true);
	}
}

void	put_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->taken = false;
	pthread_mutex_unlock(&fork->mutex);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->stop);
	pthread_mutex_destroy(&data->print);
	i = 0;
	while (i < data->amount)
	{
		pthread_mutex_destroy(&data->forks[i].mutex);
		i++;
	}
}
