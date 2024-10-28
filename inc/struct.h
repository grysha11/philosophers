/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:26:06 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/28 11:57:45 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "philo.h"
# include <stdbool.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_fork
{
	bool			taken;
	int				id;
	pthread_mutex_t	mutex;
}				t_fork;

typedef enum e_state
{
	SLEEP,
	EAT,
	THINK,
	FORK
}			t_state;

typedef struct s_philo
{
	int				id;
	int				eat_c;
	int				dead;
	int				ready;
	t_state			state;
	int				fork_l;
	int				fork_r;
	ssize_t			start_t;
	ssize_t			time;
	pthread_t		thrd;
	t_data			*data;
}				t_philo;

typedef struct s_data
{
	int				amount;
	ssize_t			t_die;
	ssize_t			t_eat;
	ssize_t			t_sleep;
	int				cycle;
	int				exit;
	pthread_mutex_t	stop;
	pthread_mutex_t	print;
	t_fork			forks[200];
	t_philo			philos[200];
}				t_data;

#endif