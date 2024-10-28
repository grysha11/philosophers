/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:17:38 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/28 14:06:52 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_util(t_philo *philo, size_t cur_t)
{
	pthread_mutex_lock(&philo->data->print);
	if (philo->state == FORK)
	{
		printf("%zu %d has taken a fork\n", cur_t, philo->id);
	}
	if (philo->state == THINK)
	{
		printf("%zu %d is thinking\n",
			cur_t, philo->id);
	}
	pthread_mutex_unlock(&philo->data->print);
}

void	print_state(t_philo *philo)
{
	size_t	cur_t;

	if (!check_podox(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->stop);
	cur_t = get_time(philo);
	pthread_mutex_unlock(&philo->data->stop);
	if (philo->state == THINK || philo->state == FORK)
		print_util(philo, cur_t);
	else if (philo->state == SLEEP)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%zu %d is sleeping\n",
			cur_t, philo->id);
		pthread_mutex_unlock(&philo->data->print);
	}
	else if (philo->state == EAT)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%zu %d is eating\n",
			cur_t, philo->id);
		pthread_mutex_unlock(&philo->data->print);
	}
}

void	ft_eat(t_philo *philo)
{
	if (!check_podox(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->stop);
	philo->state = EAT;
	pthread_mutex_unlock(&philo->data->stop);
	print_state(philo);
	ft_usleep(philo->data->t_eat);
	pthread_mutex_lock(&philo->data->stop);
	philo->eat_c += 1;
	pthread_mutex_unlock(&philo->data->stop);
	pthread_mutex_lock(&philo->data->stop);
	philo->start_t = get_time(philo);
	pthread_mutex_unlock(&philo->data->stop);
	update_forks(philo);
}

void	ft_sleep(t_philo *philo)
{
	if (!check_podox(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->stop);
	philo->state = SLEEP;
	pthread_mutex_unlock(&philo->data->stop);
	print_state(philo);
	ft_usleep(philo->data->t_sleep);
	if (!check_podox(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->stop);
	philo->state = THINK;
	pthread_mutex_unlock(&philo->data->stop);
	print_state(philo);
}

bool	init_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->stop, NULL);
	i = 0;
	while (i < data->amount)
	{
		pthread_mutex_init(&data->forks[i].mutex, NULL);
		if (i + 1 % 2 == 0)
			data->forks[i].id = i + 1 % data->amount;
		else
			data->forks[i].id = -1;
		data->forks[i].taken = false;
		i++;
	}
	return (true);
}
