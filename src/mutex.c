/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:06:03 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/23 10:34:04 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	mutex_init(pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		printf("Failed to init mutex\n");
		return (false);
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
		//printf("Failed to destroy mutex\n");
		return (false);
	}
	return (true);
}
