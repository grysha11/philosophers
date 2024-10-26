/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:09:43 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/26 15:04:03 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		printf("🎉🥳%sPhilosophers succesfuly survived ",
			COLOR_GREEN);
		printf("all of the circles !!%s\tTime is:%zu\n",
			COLOR, get_time(&(*data)->philos[i]));
		return (true);
	}
	return (false);
}

bool	check_death(t_data **data, ssize_t current_time, int i)
{
	if (current_time > (*data)->philos[i].start_t + (*data)->t_die + 10)
	{
		(*data)->philos[i].dead = true;
		(*data)->exit = 1;
		printf("😭💀%sPhilosopher ID-%d is dead\t\ttime is: %zu\t",
			COLOR_RED, (*data)->philos[i].id, get_time(&(*data)->philos[i]));
		printf("DIFFERENCE IS %zu%s\n", current_time
			- (*data)->philos[i].start_t + (*data)->t_die, COLOR);
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
					break ;  // Exit inner loop but continue outer to check all philosophers.
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
	if (philo->id % 2 == 0)
		ft_usleep(1);
	philo->ready = 1;
	philo->time = get_time(NULL);
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
