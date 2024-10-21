/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:17:38 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/21 14:27:52 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_usleep(size_t time)
{
	while (1)
	{
		if (get_time() == time)
			return ;
	}
}

void	*routine_monitor(void *arg)
{
    t_data	*data;
    int		i;
    size_t	time;
    size_t	current_time;

    data = (t_data *)arg;
    while (1)
    {
        i = 0;
        while (i < data->amount)
        {
            mutex_lock(&data->stop);
            current_time = get_time();
            if (current_time > data->philos[i].start_t + data->t_die)
            {
                time = current_time - data->philos[i].start_t;
                data->philos[i].dead = true;
                printf("😭💀%sPhilosopher ID-%d is dead difference is %zu%s\n", COLOR_RED, data->philos[i].id, time, COLOR);
                data->exit = 1;
                mutex_unlock(&data->stop);
                return (NULL);
            }
            mutex_unlock(&data->stop);
            i++;
        }
		ft_usleep(100);
    }
}

void	print_state(t_philo *philo)
{
	size_t	cur_t;

	mutex_lock(&philo->data->print);
	cur_t = get_time();
	if (philo->state == THINK)
	{
		printf("🤔💭%sPhilosopher ID-%d is thinking...%s\tTime is:%lu\n",COLOR_CYAN,
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
	if (philo->fork_l < philo->fork_r)
	{
		if (mutex_lock(&philo->data->forks[philo->fork_l]) == true)
		{
			if (mutex_lock(&philo->data->forks[philo->fork_r]) == true)
				return (true);
			else
				mutex_unlock(&philo->data->forks[philo->fork_l]);
		}
	}
	else
	{
		if (mutex_lock(&philo->data->forks[philo->fork_r]) == true)
		{
			if (mutex_lock(&philo->data->forks[philo->fork_l]) == true)
				return (true);
			else
				mutex_unlock(&philo->data->forks[philo->fork_r]);
		}
	}
	return (false);
}

void	ft_eat(t_philo *philo)
{
	int	time;

	philo->state = EAT;
	print_state(philo);
	time = philo->data->t_eat + get_time();
	ft_usleep(time);
	philo->start_t = get_time();
	mutex_unlock(&philo->data->forks[philo->fork_l]);
	mutex_unlock(&philo->data->forks[philo->fork_r]);
}

void	ft_sleep(t_philo *philo)
{
	int time;

	philo->state = SLEEP;
	print_state(philo);
	time = philo->data->t_eat + get_time();
	ft_usleep(time);
}

bool	check_death(t_data *data)
{
	if (data->exit == 1)
	{
		return (true);
	}
	return (false);
}

void	*routine_philo(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_death(philo->data) == true)
		{
			return (NULL);
		}
		print_state(philo);
		if (try_forks(philo) == true)
		{
			if (check_death(philo->data) == true)
			{
				return (NULL);
			}
			ft_eat(philo);
			if (check_death(philo->data) == true)
			{
				return (NULL);
			}
			ft_sleep(philo);
			if (check_death(philo->data) == true)
			{
				return (NULL);
			}
		}
	}
	return (NULL);
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
	philo->fork_l = philo->id - 1;
	philo->fork_r = philo->id % amount;
}

size_t	get_time(void)
{
	struct timeval	time;
	
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

bool	init_philos(t_data *data)
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
		if (!create_thrd(&data->philos[i].thrd, routine_philo, (void *)&data->philos[i]))
			return (false);
		i++;
	}
	return (true);
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

bool	join_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->amount)
	{
		if (!join_thrd(&data->philos[i].thrd))
			return (false);
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
