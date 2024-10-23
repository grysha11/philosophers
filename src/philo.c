/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:17:38 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/23 14:40:26 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
		printf("🤔💭%sPhilosopher ID-%d is thinking...%s\tTime is:%lu\n", COLOR_CYAN,
			philo->id, COLOR, cur_t);
	}
	else if (philo->state == SLEEP)
	{
		printf("😴💤%sPhilosopher ID-%d is sleeping...%s\tTime is:%lu\n", COLOR_CYAN,
			philo->id, COLOR, cur_t);
	}
	else if (philo->state == EAT)
	{
		printf("🍝🍴%sPhilosopher ID-%d is eating...%s\tTime is:%lu\n", COLOR_CYAN,
			philo->id, COLOR, cur_t);
	}
	mutex_unlock(&philo->data->print);
}

bool	try_forks(t_philo *philo)
{
	if (philo->data->exit == 1)
		return (false);
	print_state(philo);
	if (philo->fork_l < philo->fork_r)
	{
		if (mutex_lock(&philo->data->forks[philo->fork_l]) == true)
		{
			philo->state = FORK2;
			print_state(philo);
			if (mutex_lock(&philo->data->forks[philo->fork_r]) == true)
			{
				philo->state = FORK2;
				print_state(philo);
				return (true);
			}
			else
			{
				mutex_unlock(&philo->data->forks[philo->fork_l]);
				return (false);
			}
		}
	}
	else
	{
		if (mutex_lock(&philo->data->forks[philo->fork_r]) == true)
		{
			philo->state = FORK1;
			print_state(philo);
			if (mutex_lock(&philo->data->forks[philo->fork_l]) == true)
			{
				philo->state = FORK2;
				print_state(philo);
				return (true);
			}
			else
			{
				mutex_unlock(&philo->data->forks[philo->fork_r]);
				return (false);
			}
		}
	}
	return (false);
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

void	get_forks(t_philo *philo, int amount)
{
	philo->fork_l = philo->id - 1;
	philo->fork_r = philo->id % amount;
}

bool	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->amount)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_c = 0;
		data->philos[i].state = THINK;
		data->philos[i].dead = false;
		get_forks(&data->philos[i], data->amount);
		data->philos[i].start_t = 0;
		data->philos[i].time = 0;
		data->philos[i].data = data;
		if (!create_thrd(&data->philos[i].thrd, routine_philo, (void *)&data->philos[i]))
			return (false);
		i++;
	}
	return (true);
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

void	destroy_mutexes(t_data *data)
{
	int	i;

	mutex_destroy(&data->stop);
	mutex_destroy(&data->print);
	i = 0;
	while (i < data->amount)
	{
		mutex_destroy(&data->forks[i]);
		i++;
	}
}

void	initialize(t_data *data)
{
	pthread_t	monitor;

	init_mutexes(data);
	if (!init_philos(data))
	{
		destroy_mutexes(data);
		return ;
	}
	create_thrd(&monitor, routine_monitor, (void *)data);
	join_thrd(&monitor);
	join_philos(data);
	destroy_mutexes(data);
}
