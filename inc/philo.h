/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 09:36:47 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/23 14:39:35 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "struct.h"
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

# define TRUE 1
# define FALSE 0

# define COLOR "\033[0m"
# define COLOR_RED "\033[1;31m"
# define COLOR_GREEN "\033[1;32m"
# define COLOR_BLUE "\033[1;34m"
# define COLOR_PURPLE "\033[1;35m"
# define COLOR_CYAN "\033[1;36m"

// util functions
int		ft_atoi(char const *str);
int		ft_isdigit(int c);
size_t	get_time(t_philo *philo);
void	ft_usleep(int time);

// thread functions
bool	create_thrd(pthread_t *thread, void *routine(void *), void *arg);
bool	join_thrd(pthread_t *thread);

// mutex functions
bool	mutex_unlock(pthread_mutex_t *mutex);
bool	mutex_lock(pthread_mutex_t *mutex);
bool	mutex_destroy(pthread_mutex_t *mutex);
bool	mutex_init(pthread_mutex_t *mutex);

//init functions
void	initialize(t_data *data);
bool	init_philos(t_data *data);
bool	init_mutexes(t_data *data);
bool	join_philos(t_data *data);
void	destroy_mutexes(t_data *data);

//routine functions
void	*routine_philo(void *arg);
void	*routine_monitor(void *arg);
void	print_state(t_philo *philo);
bool	try_forks(t_philo *philo);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);

#endif