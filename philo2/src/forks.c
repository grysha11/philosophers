/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:25:38 by hzakharc          #+#    #+#             */
/*   Updated: 2024/11/03 12:26:25 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	fork_action(int id, t_fork *take, bool status)
{
	bool	return_val;

	return_val = false;
	pthread_mutex_lock(&take->mutex);
	if (id != take->last && take->taken != status)
	{
		take->taken = status;
		return_val = true;
	}
	pthread_mutex_unlock(&take->mutex);
	return (return_val);
}

bool	try_forks(t_philo *philo)
{
	if (philo->data->amount == 1)
		return (false);
	if (!fork_action(philo->id, philo->fork_l, true))
		return (false);
	if (!fork_action(philo->id, philo->fork_r, true))
	{
		fork_action(philo->id, philo->fork_l, false);
		return (false);
	}
	return (true);
}

bool	update_forks(t_philo *philo)
{
	if (!fork_action(philo->id, philo->fork_l, false))
		return (false);
	if (!fork_action(philo->id, philo->fork_r, false))
	{
		fork_action(philo->id, philo->fork_l, true);
		return (false);
	}
	philo->fork_l->last = philo->id;
	philo->fork_r->last = philo->id;
	return (true);
}

void	eat(t_philo *philo)
{
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	pthread_mutex_lock(&philo->data->stop);
	philo->state = EAT;
	philo->time_e = get_time();
	pthread_mutex_unlock(&philo->data->stop);
	ft_usleep(philo->data->t_eat);
	pthread_mutex_lock(&philo->data->end_c);
	update_forks(philo);
	philo->eat_c++;
	pthread_mutex_unlock(&philo->data->end_c);
}
