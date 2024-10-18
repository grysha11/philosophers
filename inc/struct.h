/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:26:06 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/18 18:31:11 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "philo.h"

typedef enum e_state
{
	SLEEP,
	EAT,
	THINK
}			t_state;

typedef struct s_data
{
	int				amount;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				cycle;
	int				exit;
	pthread_mutex_t	stop;
	pthread_mutex_t	print;
	pthread_mutex_t	forks[200];
}				t_data;

typedef struct s_philo
{
	int				id;
	int				dead;
	t_state			state;
	int				fork_l;
	int				fork_r;
	unsigned long	start_t;
	t_data			*data;
}				t_philo;

#endif