/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:18:39 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/29 16:45:22 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	take_forks(t_philo *philo, t_fork *first, t_fork *second)
{
	pthread_mutex_lock(&first->mutex);
	if (first->taken == false)
	{
		pthread_mutex_lock(&second->mutex);
		if (second->taken == false)
		{
			first->taken = true;
			first->id = philo->id;
			second->taken = true;
			second->id = philo->id;
			pthread_mutex_unlock(&first->mutex);
			pthread_mutex_unlock(&second->mutex);
			return (true);
		}
		pthread_mutex_unlock(&first->mutex);
		pthread_mutex_unlock(&second->mutex);
		return (false);
	}
	pthread_mutex_unlock(&first->mutex);
	return (false);
}

bool	try_forks(t_philo *philo)
{
	if (philo->fork_l.id < philo->fork_r.id)
		return (take_forks(philo, &philo->fork_l, &philo->fork_r));
	else
		retunr (take_forks(philo, &philo->fork_r, &philo->fork_l));
}

void	eat(t_philo *philo)
{
	if (!try_forks(philo))
		return ;
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	pthread_mutex_lock(&philo->data->stop);
	philo->time_e = get_time();
	pthread_mutex_unlock(&philo->data->stop);
	ft_usleep(philo->data->t_eat);
	pthread_mutex_lock(&philo->data->stop);
	philo->eat_c++;
	pthread_mutex_unlock(&philo->data->stop);
}

void	print_state(t_philo *philo, char *msg)
{
	const size_t	time = get_time() - philo->start_t;

	if (philo->time_e > philo->data->t_die)
		return ;
	pthread_mutex_lock(&philo->data->print);
	printf("%zu %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	philo->time_e = get_time();
	while (1)	//do the dead checker
	{
		if (philo->data->amount == 1)
			ft_usleep(philo->data->t_die);
		eat(philo);
	}
}

bool	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->amount)
	{
		if (pthread_create(data->philos[i].thrd, NULL, routine,
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
		if (pthread_join(&data->philos[i], NULL) != 0)
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
	pthread_mutex_init(&data->print, NULL);
	while (i < data->amount)
	{
		data->forks[i].taken = false;
		data->forks[i].id = -1;
		pthread_mutex_init(&data->forks[i].mutex, NULL);
		i++;
	}
}

void	init_philos(t_data *data)
{
	int	i;

	while (i < data->amount)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_c = 0;
		data->philos[i].state = THINK;
		data->philos[i].data = data;
		data->philos[i].fork_r = data->forks[i];
		data->philos[i].start_t = get_time();
		data->philos[i].fork_l = data->forks[(i + 1) % data->amount];
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
