/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:44:37 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/23 14:40:39 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_isdigit(int c)
{
	if (c == '-' || c == '+')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int	check_space(int c)
{
	if ((c > 8 && c < 14)
		|| (c == 32))
		return (8192);
	return (0);
}

int	ft_atoi(char const *str)
{
	long long int	n;
	long long int	check;
	int				sign;

	n = 0;
	sign = 1;
	while (*str && check_space(*str))
		str++;
	if (*str == 45 || *str == 43)
	{
		if (*str == 45)
			sign *= -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		check = n;
		n = n * 10 + sign * (*str - 48);
		if (n > check && sign < 0)
			return (0);
		if (n < check && sign > 0)
			return (-1);
		str++;
	}
	return (n);
}

size_t	get_time(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (philo)
		return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - philo->time);
	else
		return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(int time)
{
	ssize_t	i;

	i = get_time(NULL);
	while (1)
		if ((int)(get_time(NULL) - i) >= time)
			break ;
}
