/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:17:38 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/25 15:29:42 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_util(t_philo *philo, size_t cur_t)
{
	if (philo->state == FORK1)
	{
		printf("Philo ID-%d took a fork\n", philo->id);
	}
	if (philo->state == FORK2)
	{
		printf("Philo ID-%d took a fork\n", philo->id);
	}
	if (philo->state == THINK)
	{
		printf("🤔💭%sPhilosopher ID-%d is thinking...%s\tTime is:%lu\n",
			COLOR_CYAN, philo->id, COLOR, cur_t);
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
	if (philo->state == THINK || philo->state == FORK1 || philo->state == FORK2)
		print_util(philo, cur_t);
	else if (philo->state == SLEEP)
	{
		printf("😴💤%sPhilosopher ID-%d is sleeping...%s\tTime is:%lu\n",
			COLOR_CYAN, philo->id, COLOR, cur_t);
	}
	else if (philo->state == EAT)
	{
		printf("🍝🍴%sPhilosopher ID-%d is eating...%s\tTime is:%lu\n",
			COLOR_CYAN, philo->id, COLOR, cur_t);
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
	philo->start_t = get_time(philo);
	mutex_unlock(&philo->data->forks[philo->fork_l]);
	mutex_unlock(&philo->data->forks[philo->fork_r]);
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
		if (!mutex_init(&data->forks[i]))
		{
			return (false);
		}
		i++;
	}
	return (true);
}
