/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bburguie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:04:03 by bburguie          #+#    #+#             */
/*   Updated: 2023/05/17 17:04:04 by bburguie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	split_1(t_arg *arg)
{
	ft_print(arg, "is thinking", get_time());
	if (arg->n == 0)
		pthread_mutex_lock(&arg->vars->forks[arg->vars->total - 1]);
	else
		pthread_mutex_lock(&arg->vars->forks[arg->n - 1]);
	if (is_over(arg))
	{
		if (arg->n == 0)
			pthread_mutex_unlock(&arg->vars->forks[arg->vars->total - 1]);
		else
			pthread_mutex_unlock(&arg->vars->forks[arg->n - 1]);
		return (0);
	}
	ft_print(arg, "has taken left fork", get_time());
	if (arg->vars->total == 1)
		return (0);
	return (1);
}

int	split_2(t_arg *arg)
{
	pthread_mutex_lock(&arg->vars->forks[arg->n]);
	if (is_over(arg))
	{
		if (arg->n == 0)
			pthread_mutex_unlock(&arg->vars->forks[arg->vars->total - 1]);
		else
			pthread_mutex_unlock(&arg->vars->forks[arg->n - 1]);
		pthread_mutex_unlock(&arg->vars->forks[arg->n]);
		return (0);
	}
	ft_print(arg, "has taken right fork", get_time());
	if (is_over(arg))
	{
		if (arg->n == 0)
			pthread_mutex_unlock(&arg->vars->forks[arg->vars->total - 1]);
		else
			pthread_mutex_unlock(&arg->vars->forks[arg->n - 1]);
		pthread_mutex_unlock(&arg->vars->forks[arg->n]);
		return (0);
	}
	return (1);
}

int	split_3(t_arg *arg)
{
	ft_print(arg, "is eating", get_time());
	pthread_mutex_lock(&arg->ttd_mutex.mutex);
	arg->ttd_mutex.value = ((unsigned int) get_time());
	pthread_mutex_unlock(&arg->ttd_mutex.mutex);
	usleep(arg->vars->tte * 1000);
	arg->has_eaten += 1;
	if (arg->has_eaten == arg->vars->me)
	{
		pthread_mutex_lock(&arg->vars->has_all_eaten->mutex);
		arg->vars->has_all_eaten->value += 1;
		pthread_mutex_unlock(&arg->vars->has_all_eaten->mutex);
	}
	pthread_mutex_unlock(&arg->vars->forks[arg->n]);
	if (arg->n == 0)
		pthread_mutex_unlock(&arg->vars->forks[arg->vars->total - 1]);
	else
		pthread_mutex_unlock(&arg->vars->forks[arg->n - 1]);
	if (is_over(arg))
		return (0);
	ft_print(arg, "is sleeping", get_time());
	usleep(arg->vars->tts * 1000);
	return (1);
}
