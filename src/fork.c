/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:26:20 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/27 15:47:53 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	update_forks(t_philo *philo)
{
	mutex_lock(&philo->data->forks[philo->fork_l].mutex);
	philo->data->forks[philo->fork_l].taken = false;
	philo->data->forks[philo->fork_l].id = -1;
	mutex_unlock(&philo->data->forks[philo->fork_l].mutex);
	mutex_lock(&philo->data->forks[philo->fork_r].mutex);
	philo->data->forks[philo->fork_r].taken = false;
	philo->data->forks[philo->fork_r].id = -1;
	mutex_unlock(&philo->data->forks[philo->fork_r].mutex);
}

bool	take_fork(t_philo *philo, t_fork *fork)
{
	mutex_lock(&fork->mutex);
	if (fork->taken == true && fork->id != philo->id)
	{
		mutex_unlock(&fork->mutex);
		return (false);
	}
	else
	{
		fork->taken = true;
		fork->id = philo->id;
		mutex_unlock(&fork->mutex);
		return (true);
	}
}

bool	try_forks(t_philo *philo)
{
	if (philo->data->exit == 1)
		return (false);
	if (philo->data->amount == 1)
		return (false);
	if (philo->fork_l < philo->fork_r)
	{
		if (take_fork(philo, &philo->data->forks[philo->fork_l]) == true
			&& take_fork(philo, &philo->data->forks[philo->fork_r]) == true)
		{
			philo->state = FORK;
			print_state(philo);
			return (true);
		}
	}
	else
	{
		if (take_fork(philo, &philo->data->forks[philo->fork_r]) == true
			&& take_fork(philo, &philo->data->forks[philo->fork_l]) == true)
		{
			philo->state = FORK;
			print_state(philo);
			return (true);
		}
	}
	return (false);
}

void	get_forks(t_philo *philo, int amount)
{
	philo->fork_l = philo->id;
	philo->fork_r = philo->id % amount;
}
