/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:09:43 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/29 11:55:56 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	time_checker_d(ssize_t current_time, t_data *data, int i)
{
	pthread_mutex_lock(&data->stop);
	if (current_time >= data->philos[i].start_t + data->t_die + 9
		&& data->philos[i].state != EAT)
	{
		pthread_mutex_unlock(&data->stop);
		return (true);
	}
	pthread_mutex_unlock(&data->stop);
	return (false);
}

bool	check_death(t_data **data, int i)
{
	ssize_t	current_time;

	pthread_mutex_lock(&(*data)->stop);
	current_time = get_time(&(*data)->philos[i]);
	pthread_mutex_unlock(&(*data)->stop);
	if (time_checker_d(current_time, *data, i))
	{
		pthread_mutex_lock(&(*data)->stop);
		(*data)->philos[i].dead = true;
		(*data)->exit = 1;
		pthread_mutex_unlock(&(*data)->stop);
		pthread_mutex_lock(&(*data)->print);
		printf("%zu %d died\n", current_time, (*data)->philos[i].id);
		pthread_mutex_unlock(&(*data)->print);
		return (true);
	}
	return (false);
}

bool	check_podox(t_data *data)
{
	pthread_mutex_lock(&data->stop);
	if (data->exit == 1)
	{
		pthread_mutex_unlock(&data->stop);
		return (false);
	}
	pthread_mutex_unlock(&data->stop);
	return (true);
}

void	*routine_monitor(void *arg)
{
	t_data	*data;
	int		i;
	int		e_flag;

	data = (t_data *)arg;
	while (check_podox(data))
	{
		pthread_mutex_lock(&data->stop);
		i = 0;
		e_flag = 0;
		pthread_mutex_unlock(&data->stop);
		while (i < data->amount)
		{
			if (routine_monitor_util(&data, &e_flag, i) == true)
				break ;
			pthread_mutex_lock(&data->stop);
			i++;
			pthread_mutex_unlock(&data->stop);
		}
		if (ultra_eat_check(e_flag, &data))
			break ;
	}
	return (NULL);
}

void	*routine_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->stop);
	philo->ready = 1;
	philo->time = get_time(NULL);
	pthread_mutex_unlock(&philo->data->stop);
	print_state(philo);
	while (1)
	{
		if (!check_podox(philo->data))
			break ;
		if (try_forks(philo) == true)
		{
			ft_eat(philo);
			ft_sleep(philo);
		}
	}
	return (NULL);
}
