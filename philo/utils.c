/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bburguie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:11:16 by bburguie          #+#    #+#             */
/*   Updated: 2023/05/12 19:11:17 by bburguie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

static unsigned int	ft_pow(unsigned int nbr, int n)
{
	if (n == 0)
		return (1);
	if (n == 1)
		return (nbr);
	else
		return (nbr * ft_pow(nbr, n - 1));
}

unsigned int	ft_atoi(const char *nptr)
{
	char			*str;
	int				i;
	int				j;
	unsigned int	nbr;

	str = (char *) nptr;
	i = 0;
	nbr = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	j = 0;
	while (str[--i] >= '0' && str[i] <= '9')
		nbr += (str[i] - '0') * ft_pow(10, j++);
	return (nbr);
}

long long	get_time(void)
{
	struct timeval		time;
	long long			time_ms;
	static long long	base_time = 0;

	if (base_time == 0)
	{
		gettimeofday(&time, NULL);
		base_time = time.tv_sec * 1000LL + time.tv_usec / 1000;
	}
	gettimeofday(&time, NULL);
	time_ms = time.tv_sec * 1000LL + time.tv_usec / 1000;
	return (time_ms - base_time);
}

void	ft_print(t_arg *arg, const char *mess, long long time)
{
	printf("%lld %u %s\n", time, arg->n + 1, mess);
}
