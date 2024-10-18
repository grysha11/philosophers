/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc < hzakharc@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 09:36:47 by hzakharc          #+#    #+#             */
/*   Updated: 2024/10/17 10:01:13 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <limits.h>
# include "struct.h"
# include <stdbool.h>

# define TRUE 1
# define FALSE 0

# define COLOR "\033[0m"
# define COLOR_RED "\033[1;31m"
# define COLOR_GREEN "\033[1;32m"
# define COLOR_BLUE "\033[1;34m"
# define COLOR_PURPLE "\033[1;35m"
# define COLOR_CYAN "\033[1;36m"

// util functions
int		ft_atoi(char const *str);
int		ft_isdigit(int c);

//main functions
void	init_loop(t_data *data);

#endif