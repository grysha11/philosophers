/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 23:05:18 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/20 17:56:44 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	check_data(t_data data, int len)
{
	if (!(data.amount > 0 && data.amount <= 200) || !(data.t_die > 0 && data.t_die <= INT_MAX) || !(data.t_eat > 0 && data.t_eat <= INT_MAX) || !(data.t_sleep > 0 && data.t_sleep <= INT_MAX))
	{
		printf("%sERROR%s: Non-numeric argument:\n\tTry: %s./philo num_of_philos time_to_die time_to_eat time_to_sleep (num_to_eat)%s\n", COLOR_RED, COLOR, COLOR_CYAN, COLOR);
		return (false);
	}
	else if (len == 6)
	{
		if (!(data.cycle > 0 && data.cycle <= INT_MAX))
		{
			printf("%sERROR%s: Non-numeric argument:\n\tTry: %s./philo num_of_philos time_to_die time_to_eat time_to_sleep (num_to_eat)%s\n", COLOR_RED, COLOR, COLOR_CYAN, COLOR);
			return (false);
		}
	}
	return (true);
}

bool	init_data(t_data *data, char **av, int len)
{
	data->amount = atoi(av[1]);
	data->exit = 0;
	data->t_die = atoi(av[2]);
	data->t_eat = atoi(av[3]);
	data->t_sleep = atoi(av[4]);
	if (len == 6)
		data->cycle = atoi(av[5]);
	else
		data->cycle = 1;
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
				printf("%sERROR%s: privetNon-numeric argument:\n\tTry: %s./philo num_of_philos time_to_die time_to_eat time_to_sleep (num_to_eat)%s\n", COLOR_RED, COLOR, COLOR_CYAN, COLOR);
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
		printf("%sERROR%s: Incorrect amount of arguments:\n\tTry: %s./philo num_of_philos time_to_die time_to_eat time_to_sleep (num_to_eat)%s\n", COLOR_RED, COLOR, COLOR_CYAN, COLOR);
		return (1);
	}
}
