/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:09:43 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/24 12:57:21 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine_monitor(void *arg)
{
	t_data	*data;
	int		i;
	int		e_flag;
	size_t	current_time;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		e_flag = 0;
		while (i < data->amount)
		{
			mutex_lock(&data->stop);
			current_time = get_time(&data->philos[i]);
			if (current_time > data->philos[i].start_t + data->t_die + 10)
			{
				data->philos[i].dead = true;
				data->exit = 1;
				printf("%zu: CURRENT TIME\n", current_time);
				printf("%zu: START TIME OF PHILO\n", data->philos[i].start_t);
				printf("😭💀%sPhilosopher ID-%d is dead\t\ttime is: %zu\tDIFFERENCE IS %zu%s\n", COLOR_RED, data->philos[i].id, get_time(&data->philos[i]), current_time - data->philos[i].start_t + data->t_die, COLOR);
				mutex_unlock(&data->stop);
				return (NULL);
			}
			if (data->cycle != -1 && data->philos[i].eat_c >= data->cycle)
				e_flag = 1;
			if (e_flag == 1)
			{
				data->exit = 1;
				printf("🎉🥳%sPhilosophers succesfuly survived all of the circles !!%s\tTime is:%zu\n", COLOR_GREEN, COLOR, get_time(&data->philos[i]));
				mutex_unlock(&data->stop);
				return (NULL);
			}
			mutex_unlock(&data->stop);
			i++;
		}
	}
}

void	*routine_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		philo->state = THINK;
		ft_usleep(1);
	}
	philo->time = get_time(NULL);
	while (1)
	{
		if (philo->data->exit == 1)
			break ;
		if (try_forks(philo))
		{
			ft_eat(philo);
			ft_sleep(philo);
		}
	}
	mutex_unlock(&philo->data->forks[philo->fork_l]);
	mutex_unlock(&philo->data->forks[philo->fork_r]);
	return (NULL);
}
