/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:18:06 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/29 14:38:26 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	err_inc_parse(char *first_message)
{
	printf("%sERROR %s: %s:\n\t", COLOR_RED, first_message, COLOR);
	printf("Try: %s./philo num_of_philos time_to_die ", COLOR_CYAN);
	printf("time_to_eat time_to_sleep (num_to_eat)%s\n", COLOR);
}

bool	check_data(t_data data, int len)
{
	if (!(data.amount > 0 && data.amount <= 200)
		|| !(data.t_die >= 120 && data.t_die <= INT_MAX)
		|| !(data.t_eat >= 60 && data.t_eat <= INT_MAX)
		|| !(data.t_sleep >= 60 && data.t_sleep <= INT_MAX))
	{
		err_inc_parse("Number is too big or too small");
		return (false);
	}
	else if (len == 6)
	{
		if (!(data.cycle > 0 && data.cycle <= INT_MAX))
		{
			err_inc_parse("Number is too big");
			return (false);
		}
	}
	return (true);
}

bool	init_data(t_data *data, char **av, int len)
{
	data->amount = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->exit = 0;
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (len == 6)
		data->cycle = ft_atoi(av[5]);
	else
		data->cycle = -1;
	if (!check_data(*data, len))
		return (false);
	return (true);
}

bool	check_input(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i] != NULL)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (!ft_isdigit(av[i][j]))
			{
				err_inc_parse("Non-numeric argument");
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (check_input(av) && init_data(&data, av, ac))
			initialize(&data);
	}
	else
	{
		err_inc_parse("Incorrect number of arguments");
		return (1);
	}
	return (0);
}
