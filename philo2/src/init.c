/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:18:39 by hzakharc          #+#    #+#             */
/*   Updated: 2024/11/01 14:38:12 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	take_forks(t_fork *first, t_fork *second)
{
	pthread_mutex_lock(&first->mutex);
	pthread_mutex_lock(&second->mutex);
	if (first->taken == false)
	{
		if (second->taken == false)
		{
			first->taken = true;
			second->taken = true;
			pthread_mutex_unlock(&first->mutex);
			pthread_mutex_unlock(&second->mutex);
			return (true);
		}
	}
	pthread_mutex_unlock(&first->mutex);
	pthread_mutex_unlock(&second->mutex);
	return (false);
}

bool	try_forks(t_philo *philo)
{
	if (philo->data->amount == 1)
		return (false);
	if (philo->fork_l->id < philo->fork_r->id)
	{
		if (!take_forks(philo->fork_l, philo->fork_r))
			return (false);
	}
	else
	{
		if (!take_forks(philo->fork_r, philo->fork_l))
			return (false);
	}
	return (true);
}

void	update_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_l->mutex);
	philo->fork_l->taken = false;
	pthread_mutex_unlock(&philo->fork_l->mutex);
	pthread_mutex_lock(&philo->fork_r->mutex);
	philo->fork_r->taken = false;
	pthread_mutex_unlock(&philo->fork_r->mutex);
}

void	eat(t_philo *philo)
{
	if (!try_forks(philo))
		return ;
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	pthread_mutex_lock(&philo->data->stop);
	philo->state = EAT;
	philo->time_e = get_time();
	pthread_mutex_unlock(&philo->data->stop);
	ft_usleep(philo->data->t_eat);
	update_forks(philo);
	pthread_mutex_lock(&philo->data->stop);
	philo->eat_c++;
	pthread_mutex_unlock(&philo->data->stop);
}

void	print_state(t_philo *philo, char *msg)
{
	const size_t	time = get_time() - philo->start_t;

	pthread_mutex_lock(&philo->data->stop);
	if (philo->data->exit == 1)
	{
		pthread_mutex_unlock(&philo->data->stop);
		return ;
	}
	pthread_mutex_unlock(&philo->data->stop);
	pthread_mutex_lock(&philo->data->print);
	printf("%lu %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print);
}

void	sleeep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->stop);
	philo->state = SLEEP;
	pthread_mutex_unlock(&philo->data->stop);
	print_state(philo, "is sleeping");
	ft_usleep(philo->data->t_sleep);
	print_state(philo, "is thinking");
	pthread_mutex_lock(&philo->data->stop);
	philo->state = THINK;
	pthread_mutex_unlock(&philo->data->stop);
}

bool	check_meals(t_data *data)
{
	int	i;
	int	flag;

	i = 0;
	if (data->cycle == -1)
		return (false);
	flag = 0;
	while (i < data->amount)
	{
		if (data->philos[i].eat_c >= data->cycle)
			flag = 1;
		i++;
	}
	if (flag == 1)
		return (true);
	return (false);
}

bool	dead_check(t_philo *philo)
{
	const size_t	time = get_time();

	if (philo->data->exit == 1)
		return (false);
	if (time - philo->time_e >= philo->data->t_die)
	{
		pthread_mutex_lock(&philo->data->print);
		//printf("%zu %d died\t%zu - %zu\n", time - philo->start_t, philo->id, time - philo->time_e, philo->data->t_die);
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_lock(&philo->data->stop);
		philo->data->exit = 1;
		pthread_mutex_unlock(&philo->data->stop);
		return (false);
	}
	if (check_meals(philo->data) == true)
		return (false);
	return (true);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	philo->time_e = get_time();
	while (1)
	{
		if (!dead_check(philo))
			break;
		if (philo->data->amount == 1)
			ft_usleep(philo->data->t_die);
		eat(philo);
		sleeep(philo);
	}
	return (NULL);
}

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
	pthread_mutex_init(&data->print, NULL);
	while (i < data->amount)
	{
		data->forks[i].taken = false;
		data->forks[i].id = i;
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
		//printf("%d id, left fork %d, right fork %d\n", data->philos[i].id, (i + 1) % data->amount, i);
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
