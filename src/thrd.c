/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thrd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:05:52 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/23 14:10:20 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	create_thrd(pthread_t *thread, void *routine(void *), void *arg)
{
	if (pthread_create(thread, NULL, routine, arg) != 0)
	{
		printf("Failed to create thread\n");
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
