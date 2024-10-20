/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:17:38 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/20 18:01:27 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine_monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->amount)
		{
			mutex_lock(&data->stop);
			if (get_time() - data->philos[i].start_t > data->t_die)
			{
				data->philos[i].dead = true;
				data->exit = 1;
				mutex_lock(&data->print);
				printf("😭💀%sPhilosopher ID-%d is dead%s\n", COLOR_RED, data->philos[i].id, COLOR);
				mutex_unlock(&data->print);
				mutex_unlock(&data->stop);
				return (NULL);
			}
			mutex_unlock(&data->stop);
			i++;
		}
		usleep(100);
	}
}

void	print_state(t_philo *philo)
{
	if (philo->state == THINK)
	{
		mutex_lock(&philo->data->print);
		printf("🤔💭%sPhilosopher ID-%d is thinking...%s\n",COLOR_CYAN,
			philo->id, COLOR);
		mutex_unlock(&philo->data->print);
	}
	else if (philo->state == SLEEP)
	{
		mutex_lock(&philo->data->print);
		printf("😴💤%sPhilosopher ID-%d is sleeping...%s\n", COLOR_CYAN,
			philo->id, COLOR);
		mutex_unlock(&philo->data->print);
	}
	else if (philo->state == EAT)
	{
		mutex_lock(&philo->data->print);
		printf("🍝🍴%sPhilosopher ID-%d is eating...%s\n", COLOR_CYAN,
			philo->id, COLOR);
		mutex_unlock(&philo->data->print);
	}
	usleep(100);
}

bool	try_forks(t_philo *philo)
{
	if (mutex_lock(&philo->data->forks[philo->fork_l]) == true &&
	mutex_lock(&philo->data->forks[philo->fork_r]) == true)
		return (true);
	return (false);
}

void	ft_eat(t_philo *philo)
{
	philo->state = EAT;
	print_state(philo);
	usleep(philo->data->t_eat * 1000);
	mutex_unlock(&philo->data->forks[philo->fork_l]);
	mutex_unlock(&philo->data->forks[philo->fork_r]);
}

void	ft_sleep(t_philo *philo)
{
	philo->state = SLEEP;
	print_state(philo);
	usleep(philo->data->t_sleep * 1000);
}

void	*routine_philo(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		print_state(philo);
		if (try_forks(philo) == true)
		{
			ft_eat(philo);
			ft_sleep(philo);
		}
		if (philo->data->exit == 1)
			return (NULL);
	}
}

bool	create_thrd(pthread_t *thread, void *routine(void *), void *arg)
{
	if (pthread_create(thread, NULL, routine, arg) != 0)
	{
		printf("Failed to create thread\n");
		return (false);
	}
	return (true);
}

void	get_forks(t_philo *philo, int amount)
{
	if (philo->id - 1 == amount)
	{
		philo->fork_l = 0;
		philo->fork_r = amount;
	}
	else
	{
		philo->fork_l = philo->id - 1;
		philo->fork_r = philo->id;
	}
}

size_t	get_time(void)
{
	struct timeval	time;
	
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->amount)
	{
		data->philos[i].id = i + 1;
		data->philos[i].state = THINK;
		data->philos[i].dead = false;
		get_forks(&data->philos[i], data->amount);
		data->philos[i].start_t = get_time();
		data->philos[i].data = data;
		create_thrd(&data->philos[i].thrd, routine_philo, (void *)data);
		i++;
	}
}

bool	mutex_unlock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex) != 0)
	{
		printf("Failed to unlock mutex\n");
		return (false);
	}
	return (true);
}

bool	mutex_lock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex) != 0)
	{
		printf("Failed to lock mutex\n");
		return (false);
	}
	return (true);
}

bool	mutex_destroy(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex) != 0)
	{
		printf("Failed to destroy mutex\n");
		return (false);
	}
	return (true);
}

bool	mutex_init(pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		printf("Failed to init mutex\n");
		return (false);
	}
	return (true);
}

bool	join_thrd(pthread_t *thread)
{
	if (pthread_join(*thread, NULL) != 0)
	{
		printf("Failed to join thread\n");
		return (false);
	}
	return (true);
}

void	init_mutexes(t_data *data)
{
	int	i;

	mutex_init(&data->print);
	mutex_init(&data->stop);
	i = 0;
	while (i < data->amount)
	{
		mutex_init(&data->forks[i]);
		i++;
	}
}

void	join_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->amount)
	{
		join_thrd(&data->philos[i].thrd);
		i++;
	}
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
	init_philos(data);
	create_thrd(&monitor, routine_monitor, (void *)data);
	join_thrd(&monitor);
	join_philos(data);
	destroy_mutexes(data);
}
