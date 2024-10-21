/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:26:06 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/21 17:02:10 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "philo.h"
# include <stdbool.h>
# include <pthread.h>

typedef struct s_data	t_data;

typedef enum e_state
{
	SLEEP,
	EAT,
	THINK
}			t_state;

typedef struct s_philo
{
	int				id;
	int				dead;
	t_state			state;
	int				fork_l;
	int				fork_r;
	unsigned long	start_t;
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
	pthread_mutex_t	forks[200];
	t_philo			philos[200];
}				t_data;

#endif