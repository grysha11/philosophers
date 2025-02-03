/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:17:19 by hzakharc          #+#    #+#             */
/*   Updated: 2024/11/03 12:29:56 by hzakharc         ###   ########.fr       */
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

# define COLOR "\033[0m"
# define COLOR_RED "\033[1;31m"
# define COLOR_GREEN "\033[1;32m"
# define COLOR_BLUE "\033[1;34m"
# define COLOR_PURPLE "\033[1;35m"
# define COLOR_CYAN "\033[1;36m"

//		init functions
void	initialize(t_data *data);
void	init_philos(t_data *data);
void	init_mutexes(t_data *data);
bool	join_threads(t_data *data);
bool	create_threads(t_data *data);

//		routine functions
void	*routine(void *arg);
bool	dead_check(t_philo *philo);
bool	check_meals(t_data *data);
bool	check_podox(t_philo *philo);

//		instructions
void	sleeep(t_philo *philo);
void	eat(t_philo *philo);
void	print_state(t_philo *philo, char *msg);

//		forks
bool	try_forks(t_philo *philo);
bool	fork_action(int id, t_fork *take, bool status);

//		utils
size_t	get_time(void);
int		ft_usleep(size_t time);
bool	is_digit(char *str);
int		ft_atoi(char *str);

#endif