/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:17:38 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/27 15:47:47 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_util(t_philo *philo, size_t cur_t)
{
	if (philo->state == FORK)
	{
		printf("%zu %d has taken a fork\n", cur_t, philo->id);
	}
	if (philo->state == THINK)
	{
		printf("%zu %d is thinking\n",
			cur_t, philo->id);
	}
}

void	print_state(t_philo *philo)
{
	size_t	cur_t;

	mutex_lock(&philo->data->print);
	if (philo->data->exit == 1)
	{
		mutex_unlock(&philo->data->print);
		return ;
	}
	cur_t = get_time(philo);
	if (philo->state == THINK || philo->state == FORK)
		print_util(philo, cur_t);
	else if (philo->state == SLEEP)
	{
		printf("%zu %d is sleeping\n",
			cur_t, philo->id);
	}
	else if (philo->state == EAT)
	{
		printf("%zu %d is eating\n",
			cur_t, philo->id);
	}
	mutex_unlock(&philo->data->print);
}

void	ft_eat(t_philo *philo)
{
	if (philo->data->exit == 1)
		return ;
	philo->state = EAT;
	print_state(philo);
	ft_usleep(philo->data->t_eat);
	philo->eat_c += 1;
	update_forks(philo);
	philo->start_t = get_time(philo);
}

void	ft_sleep(t_philo *philo)
{
	if (philo->data->exit == 1)
		return ;
	philo->state = SLEEP;
	print_state(philo);
	ft_usleep(philo->data->t_sleep);
	if (philo->data->exit == 1)
		return ;
	philo->state = THINK;
	print_state(philo);
}

bool	init_mutexes(t_data *data)
{
	int	i;

	if (!mutex_init(&data->print) || !mutex_init(&data->stop))
	{
		return (false);
	}
	i = 0;
	while (i < data->amount)
	{
		if (!mutex_init(&data->forks[i].mutex))
		{
			return (false);
		}
		if (i + 1 % 2 == 0)
			data->forks[i].id = i + 1 % data->amount;
		else
			data->forks[i].id = -1;
		data->forks[i].taken = false;
		i++;
	}
	return (true);
}
