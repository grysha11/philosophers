/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:26:20 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/28 14:09:43 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	update_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->fork_l].mutex);
	philo->data->forks[philo->fork_l].taken = false;
	philo->data->forks[philo->fork_l].id = -1;
	pthread_mutex_unlock(&philo->data->forks[philo->fork_l].mutex);
	pthread_mutex_lock(&philo->data->forks[philo->fork_r].mutex);
	philo->data->forks[philo->fork_r].taken = false;
	philo->data->forks[philo->fork_r].id = -1;
	pthread_mutex_unlock(&philo->data->forks[philo->fork_r].mutex);
}

bool	try_left(t_philo *philo)
{
	if (take_fork(philo, &philo->data->forks[philo->fork_l]) == true)
	{
		if (take_fork(philo, &philo->data->forks[philo->fork_r]) == true)
		{
			pthread_mutex_lock(&philo->data->stop);
			philo->state = FORK;
			pthread_mutex_unlock(&philo->data->stop);
			print_state(philo);
			return (true);
		}
		put_fork(&philo->data->forks[philo->fork_l]);
		return (false);
	}
	return (false);
}

bool	try_right(t_philo *philo)
{
	if (take_fork(philo, &philo->data->forks[philo->fork_r]) == true)
	{
		if (take_fork(philo, &philo->data->forks[philo->fork_l]) == true)
		{
			pthread_mutex_lock(&philo->data->stop);
			philo->state = FORK;
			pthread_mutex_unlock(&philo->data->stop);
			print_state(philo);
			return (true);
		}
		put_fork(&philo->data->forks[philo->fork_r]);
		return (false);
	}
	return (false);
}

bool	try_forks(t_philo *philo)
{
	if (!check_podox(philo->data))
		return (false);
	if (philo->data->amount == 1)
		return (false);
	if (philo->fork_l < philo->fork_r)
		return (try_left(philo));
	else
		return (try_right(philo));
	return (false);
}

void	get_forks(t_philo *philo, int amount)
{
	philo->fork_l = philo->id;
	philo->fork_r = philo->id + 1 % amount;
}
