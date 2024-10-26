/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:26:20 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/26 15:21:01 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	try_left(t_philo *philo)
{
	if (philo->data->forks_check[philo->fork_l] != 1)
	{
		mutex_lock(&philo->data->forks[philo->fork_l]);
		philo->data->forks_check[philo->fork_l] = 1;
		philo->state = FORK1;
		print_state(philo);
		if (philo->data->forks_check[philo->fork_r] != 1)
		{
			mutex_lock(&philo->data->forks[philo->fork_l]);
			philo->data->forks_check[philo->fork_r] = 1;
			philo->state = FORK2;
			print_state(philo);
			return (true);
		}
		else
		{
			mutex_unlock(&philo->data->forks[philo->fork_l]);
			philo->data->forks_check[philo->fork_l] = 0;
			return (false);
		}
	}
	return (false);
}

bool	try_right(t_philo *philo)
{
	if (philo->data->forks_check[philo->fork_r] != 1)
	{
		mutex_lock(&philo->data->forks[philo->fork_r]);
		philo->data->forks_check[philo->fork_r] = 1;
		philo->state = FORK2;
		print_state(philo);
		if (philo->data->forks_check[philo->fork_l] != 1)
		{
			mutex_lock(&philo->data->forks[philo->fork_l]);
			philo->data->forks_check[philo->fork_l] = 1;
			philo->state = FORK1;
			print_state(philo);
			return (true);
		}
		else
		{
			mutex_unlock(&philo->data->forks[philo->fork_r]);
			philo->data->forks_check[philo->fork_r] = 0;
			return (false);
		}
	}
	return (false);
}

bool	try_forks(t_philo *philo)
{
	if (philo->data->exit == 1)
		return (false);
	print_state(philo);
	if (philo->fork_l < philo->fork_r)
	{
		if (try_left(philo) == true)
			return (true);
		else
			return (false);
	}
	else
	{
		if (try_right(philo) == true)
			return (true);
		else
			return (false);
	}
	return (false);
}

void	get_forks(t_philo *philo, int amount)
{
	philo->fork_l = philo->id - 1;
	philo->fork_r = philo->id % amount;
}
