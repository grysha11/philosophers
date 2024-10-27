/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:09:43 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/27 15:25:29 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

#include "../inc/philo.h"

bool	routine_monitor_util(t_data **data, int *e_flag, int i)
{
	ssize_t	current_time;

	current_time = get_time(&(*data)->philos[i]);
	if (check_death(data, current_time, i) == true)
		return (true);
	if ((*data)->cycle != -1 && (*data)->philos[i].eat_c >= (*data)->cycle)
		*e_flag = 1;
	if (*e_flag == 1)
	{
		(*data)->exit = 1;
		return (true);
	}
	return (false);
}

bool	check_death(t_data **data, ssize_t current_time, int i)
{
	if (current_time > (*data)->philos[i].start_t + (*data)->t_die + 9
		&& (*data)->philos[i].state != EAT)
	{
		(*data)->philos[i].dead = true;
		(*data)->exit = 1;
		printf("%zu %d died\n", current_time, (*data)->philos[i].id);
		return (true);
	}
	return (false);
}

void	*routine_monitor(void *arg)
{
	t_data	*data;
	int		i;
	int		e_flag;

	data = (t_data *)arg;
	while (!data->exit)
	{
		i = 0;
		e_flag = 0;
		while (i < data->amount)
		{
			mutex_lock(&data->stop);
			if (data->philos[i].ready == 1)
			{
				if (routine_monitor_util(&data, &e_flag, i) == true)
				{
					mutex_unlock(&data->stop);
					break ;
				}
			}
			mutex_unlock(&data->stop);
			i++;
		}
	}
	return (NULL);
}

void	*routine_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->ready = 1;
	philo->time = get_time(NULL);
	print_state(philo);
	while (1)
	{
		if (philo->data->exit == 1)
			break ;
		if (try_forks(philo) == true)
		{
			ft_eat(philo);
			ft_sleep(philo);
		}
		if (philo->data->exit == 1)
			break ;
	}
	return (NULL);
}
