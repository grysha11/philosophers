/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:14:43 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/18 18:30:45 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	dead_check(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->stop) != 0)
		return (true);
	pthread_mutex_unlock(&philo->data->stop);
	return (philo->dead);
}

void	routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (dead_check(philo))
	{
		//eat
		//sleep
		//think
	}
}

void	init_forks(t_data *data)
{
	int				i;

	i = 0;
	while (i < data->amount)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void	get_forks(t_philo *philo)
{
	if (philo->id - 1 == philo->data->amount)
	{
		philo->fork_l = 0;
		philo->fork_l = philo->data->amount;
	}
	else
	{
		philo->fork_l = philo->id - 1;
		philo->fork_r = philo->id;
	}
}

unsigned long	get_time(void)
{
	struct timeval	time;
	
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

bool	init_loop(t_data *data)
{
	pthread_t	philo_threads[data->amount];	
	t_philo		philos[data->amount];
	int			i;

	pthread_mutex_init(&data->print, NULL);
	init_forks(data);

	i = 0;
	while (i < data->amount)
	{
		philos[i].id = i + 1;
		philos[i].state = THINK;
		philos[i].dead = false;
		philos[i].data = &data;
		get_forks(&philos[i]);
		philos[i].start_t = get_time();
		if (pthread_create(&philo_threads[i], NULL, routine, (void *)&philos[i]) != 0)
		{
			perror("Failed to create thread");
			return (false);
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
	return (true);
}
