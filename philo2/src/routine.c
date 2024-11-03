/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:23:29 by hzakharc          #+#    #+#             */
/*   Updated: 2024/11/03 12:32:30 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	sleeep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->stop);
	philo->state = SLEEP;
	pthread_mutex_unlock(&philo->data->stop);
	print_state(philo, "is sleeping");
	ft_usleep(philo->data->t_sleep);
	print_state(philo, "is thinking");
	pthread_mutex_lock(&philo->data->stop);
	philo->state = THINK;
	pthread_mutex_unlock(&philo->data->stop);
}

bool	check_meals(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->end_c);
	if (data->cycle == -1)
	{
		pthread_mutex_unlock(&data->end_c);
		return (false);
	}
	while (i < data->amount)
	{
		if (data->philos[i].eat_c < data->cycle)
		{
			pthread_mutex_unlock(&data->end_c);
			return (false);
		}
		i++;
	}
	pthread_mutex_lock(&data->stop);
	data->exit = 1;
	pthread_mutex_unlock(&data->stop);
	pthread_mutex_unlock(&data->end_c);
	return (true);
}

bool	dead_check(t_philo *philo)
{
	const size_t	time = get_time();

	pthread_mutex_lock(&philo->data->stop);
	if (philo->data->exit == 1)
	{
		pthread_mutex_unlock(&philo->data->stop);
		return (false);
	}
	if (time - philo->time_e >= philo->data->t_die)
	{
		pthread_mutex_unlock(&philo->data->stop);
		print_state(philo, "died");
		pthread_mutex_lock(&philo->data->stop);
		philo->data->exit = 1;
		pthread_mutex_unlock(&philo->data->stop);
		return (false);
	}
	pthread_mutex_unlock(&philo->data->stop);
	return (true);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->start_t = get_time();
	philo->time_e = get_time();
	print_state(philo, "is thinking");
	while (1)
	{
		if (philo->data->amount == 1)
			ft_usleep(philo->data->t_die);
		if (!dead_check(philo) || check_meals(philo->data))
			break ;
		if (check_podox(philo))
			break ;
		if (try_forks(philo))
		{
			eat(philo);
			sleeep(philo);
		}
		if (check_podox(philo))
			break ;
	}
	return (NULL);
}

void	print_state(t_philo *philo, char *msg)
{
	const size_t	time = get_time() - philo->start_t;

	pthread_mutex_lock(&philo->data->stop);
	if (philo->data->exit == 1)
	{
		pthread_mutex_unlock(&philo->data->stop);
		return ;
	}
	pthread_mutex_unlock(&philo->data->stop);
	pthread_mutex_lock(&philo->data->print);
	printf("%lu %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print);
}
