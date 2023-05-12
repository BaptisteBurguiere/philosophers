/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bburguie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:10:25 by bburguie          #+#    #+#             */
/*   Updated: 2023/05/12 19:10:27 by bburguie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_args(int argc, char const *argv[])
{
	int	i;
	int	j;
	int	start;
	int	is_zero;

	j = 1;
	while (j < argc)
	{
		i = 0;
		is_zero = 0;
		while (argv[j][i++] == '0')
			is_zero = 1;
		start = --i;
		while (argv[j][i++])
		{
			if (argv[j][i - 1] < '0' || argv[j][i - 1] > '9')
				return (0);
		}
		if ((start == i - 1 && !is_zero) || i - 1 - start > 10
			|| (i - 1 - start == 10
				&& !(ft_strcmp(argv[j], UINT_MAX_STR) <= 0)))
			return (0);
		j++;
	}
	return (1);
}

int	is_args(int argc, char const *argv[], t_philo *vars)
{
	if (argc > 6 || argc < 5 || !is_valid_args(argc, argv))
		return (0);
	vars->total = ft_atoi(argv[1]);
	vars->ttd = ft_atoi(argv[2]);
	vars->tte = ft_atoi(argv[3]);
	vars->tts = ft_atoi(argv[4]);
	if (argc == 5)
		vars->me = 0;
	else
		vars->me = ft_atoi(argv[5]);
	return (1);
}
