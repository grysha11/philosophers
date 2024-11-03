/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:16:59 by hzakharc          #+#    #+#             */
/*   Updated: 2024/11/02 14:16:18 by hzakharc         ###   ########.fr       */
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
	int				last;
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
	int				ready;
	t_state			state;
	t_fork			*fork_l;
	t_fork			*fork_r;
	size_t			start_t;
	size_t			time_e;
	pthread_t		thrd;
	t_data			*data;
}				t_philo;

typedef struct s_data
{
	int				amount;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	int				cycle;
	int				exit;
	pthread_mutex_t	stop;
	pthread_mutex_t	print;
	pthread_mutex_t	end_c;
	t_fork			forks[200];
	t_philo			philos[200];
}				t_data;

#endif
