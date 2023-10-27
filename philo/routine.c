/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bburguie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:10:54 by bburguie          #+#    #+#             */
/*   Updated: 2023/05/12 19:10:55 by bburguie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_over(t_arg *arg)
{
	pthread_mutex_lock(&arg->vars->is_dead->mutex);
	pthread_mutex_lock(&arg->vars->has_all_eaten->mutex);
	if (arg->vars->is_dead->value == 1
		|| arg->vars->has_all_eaten->value == arg->vars->total)
	{
		pthread_mutex_unlock(&arg->vars->has_all_eaten->mutex);
		pthread_mutex_unlock(&arg->vars->is_dead->mutex);
		return (1);
	}
	pthread_mutex_unlock(&arg->vars->has_all_eaten->mutex);
	pthread_mutex_unlock(&arg->vars->is_dead->mutex);
	return (0);
}

void	*philo_ttd(void *data)
{
	t_arg	*arg;

	arg = (t_arg *) data;
	while (!is_over(arg))
	{
		pthread_mutex_lock(&arg->ttd_mutex.mutex);
		if ((unsigned int) get_time() - arg->ttd_mutex.value >= arg->vars->ttd)
		{
			if (!is_over(arg))
				ft_print(arg, "died", get_time());
			pthread_mutex_lock(&arg->vars->is_dead->mutex);
			arg->vars->is_dead->value = 1;
			pthread_mutex_unlock(&arg->vars->is_dead->mutex);
			pthread_mutex_unlock(&arg->ttd_mutex.mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&arg->ttd_mutex.mutex);
	}
	return (NULL);
}

void	*philo_routine(void *data)
{
	t_arg		*arg;
	pthread_t	ttd_thread;

	arg = (t_arg *) data;
	pthread_mutex_init(&arg->ttd_mutex.mutex, NULL);
	arg->ttd_mutex.value = (unsigned int) get_time();
	pthread_create(&ttd_thread, NULL, philo_ttd, arg);
	while (!is_over(arg))
	{
		if (!split_1(arg))
			break ;
		if (!split_2(arg))
			break ;
		if (!split_3(arg))
			break ;
	}
	pthread_join(ttd_thread, NULL);
	pthread_mutex_destroy(&arg->ttd_mutex.mutex);
	return (NULL);
}
