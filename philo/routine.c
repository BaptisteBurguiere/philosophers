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

// void	*philo_ttd(void *data)
// {
// 	t_ttd_mutex	*ttd_mutex;

// 	ttd_mutex = (t_ttd_mutex *) data;
// 	while (1)
// 	{
// 		usleep(1000);
// 		pthread_mutex_lock(&ttd_mutex->mutex);
// 		ttd_mutex->ttd -= 1;
// 		if (ttd_mutex->ttd <= 0)
// 		{
// 			pthread_mutex_lock(ttd_mutex->term);
// 			printf("%lld %u died\n", get_time(), ttd_mutex->n + 1);
// 			pthread_mutex_unlock(ttd_mutex->term);
// 			*ttd_mutex->is_dead = 1;
// 			pthread_mutex_unlock(&ttd_mutex->mutex);
// 			return (NULL);
// 		}
// 		pthread_mutex_unlock(&ttd_mutex->mutex);
// 	}
// }

void	*philo_ttd(void *data)
{
	t_arg	*arg;

	arg = (t_arg *) data;
	while (!is_over(arg))
	{
		usleep(1000);
		pthread_mutex_lock(arg->vars->ttd_mutex.mutex);
		arg->vars->ttd_mutex.value -= 1;
		if (arg->vars->ttd_mutex.value <= 0)
		{
			ft_print(arg, "died");
			pthread_mutex_lock(arg->vars->is_dead.mutex);
			arg->vars->is_dead.value = 1;
			pthread_mutex_unlock(arg->vars->is_dead.mutex);
			pthread_mutex_unlock(arg->vars->ttd_mutex.mutex);
			return (NULL);
		}
		pthread_mutex_unlock(arg->vars->ttd_mutex.mutex);
	}
	return (NULL);
}

void	philo_think(pthread_mutex_t *mutex, unsigned int n)
{
	pthread_mutex_lock(mutex);
	printf("%lld %u is thinking\n", get_time(), n);
	pthread_mutex_unlock(mutex);
}

void	philo_eat(t_arg *arg, t_ttd_mutex *ttd_mutex)
{
	if (arg->n == 0)
		pthread_mutex_lock(&arg->forks[arg->vars.total - 1]);
	else
		pthread_mutex_lock(&arg->forks[arg->n - 1]);
	pthread_mutex_lock(arg->term);
	printf("%lld %u has taken a fork\n", get_time(), arg->n + 1);
	pthread_mutex_unlock(arg->term);
	pthread_mutex_lock(&arg->forks[arg->n]);
	pthread_mutex_lock(arg->term);
	printf("%lld %u has taken a fork\n", get_time(), arg->n + 1);
	printf("%lld %u is eating\n", get_time(), arg->n + 1);
	pthread_mutex_unlock(arg->term);
	pthread_mutex_lock(&ttd_mutex->mutex);
	ttd_mutex->ttd = arg->vars.ttd;
	usleep(arg->vars.tte * 1000);
	if (arg->n == 0)
		pthread_mutex_unlock(&arg->forks[arg->vars.total - 1]);
	else
		pthread_mutex_unlock(&arg->forks[arg->n - 1]);
	pthread_mutex_unlock(&arg->forks[arg->n]);
	pthread_mutex_unlock(&ttd_mutex->mutex);
}

void	philo_sleep(t_arg *arg)
{
	pthread_mutex_lock(arg->term);
	printf("%lld %u is sleeping\n", get_time(), arg->n + 1);
	pthread_mutex_unlock(arg->term);
	usleep(arg->vars.tts * 1000);
}

// void	*philo_routine(void *data)
// {
// 	t_arg			*arg;
// 	t_ttd_mutex		ttd_mutex;
// 	pthread_t		ttd_thread;

// 	arg = (t_arg *) data;
// 	pthread_mutex_init(&ttd_mutex.mutex, NULL);
// 	ttd_mutex.ttd = arg->vars.ttd;
// 	ttd_mutex.is_dead = arg->is_dead;
// 	ttd_mutex.term = arg->term;
// 	ttd_mutex.n = arg->n;
// 	pthread_create(&ttd_thread, NULL, philo_ttd, &ttd_mutex);
// 	while (1)
// 	{
// 		philo_think(arg->term, arg->n + 1);
// 		philo_eat(arg, &ttd_mutex);
// 		philo_sleep(arg);
// 	}
// 	return (NULL);
// }

int	is_over(t_arg *arg)
{
	pthread_mutex_lock(arg->vars->is_dead.mutex);
	pthread_mutex_lock(arg->vars->has_all_eaten->mutex);
	if (arg->vars->is_dead>value == 1
		|| arg->vars->has_all_eaten == arg->vars->total)
	{
		pthread_mutex_unlock(arg->vars->is_dead.mutex);
		pthread_mutex_unlock(arg->vars->has_all_eaten->mutex);
		return (1);
	}
	return (0);
}

void	*philo_routine(void *data)
{
	t_arg		*arg;
	pthread_t	ttd_thread;

	arg = (t_arg *) data;
	pthread_mutex_init(&arg->vars->ttd_mutex.mutex);
	arg->vars->ttd_mutex.value = arg->vars.ttd;
	pthread_create(&ttd_thread, NULL, philo_ttd, arg);
	pthread_detach(ttd_thread);
	while (!is_over(arg))
	{
		ft_print(arg, "is thinking");
		if (is_over(arg))
			break ;
		if (arg->n == 0)
			pthread_mutex_lock(&arg->forks[arg->vars.total - 1]);
		else
			pthread_mutex_lock(&arg->forks[arg->n - 1]);
		ft_print(arg, "has taken left fork");
		if (is_over(arg))
			break ;
		pthread_mutex_lock(arg->term);
		ft_print(arg, "has taken right fork");
		ft_print(arg, "is eating");
		pthread_mutex_lock(arg->term);
	}
	return (NULL);
}