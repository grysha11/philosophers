/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:17:31 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/29 10:19:20 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	ultra_eat_check(int e_flag, t_data **data)
{
	if (e_flag == 1)
	{
		pthread_mutex_lock(&(*data)->stop);
		(*data)->exit = 1;
		pthread_mutex_unlock(&(*data)->stop);
		return (true);
	}
	return (false);
}
