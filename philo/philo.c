/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bburguie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:10:34 by bburguie          #+#    #+#             */
/*   Updated: 2023/05/12 19:10:35 by bburguie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_simu(t_arg *args)
{
	pthread_t		*philos;
	unsigned int	i;

	philos = malloc(args[0].vars->total * sizeof(pthread_t));
	if (philos == NULL)
		return ;
	i = 0;
	get_time();
	while (i < args[0].vars->total)
	{
		pthread_create(&philos[i], NULL, philo_routine, &args[i]);
		i++;
	}
	i = 0;
	while (i < args[0].vars->total)
	{
		pthread_join(philos[i], NULL);
		i++;
	}
	if (args[0].vars->has_all_eaten->value == args[0].vars->total)
		printf("all philosophers have eaten %u times\n", args[0].vars->me);
	free(philos);
}

void	exit_simu(t_arg *args)
{
	unsigned int	i;

	pthread_mutex_destroy(args[0].vars->term);
	free(args[0].vars->term);
	pthread_mutex_destroy(&args[0].vars->is_dead->mutex);
	free(args[0].vars->is_dead);
	pthread_mutex_destroy(&args[0].vars->has_all_eaten->mutex);
	free(args[0].vars->has_all_eaten);
	i = 0;
	while (i < args[0].vars->total)
	{
		pthread_mutex_destroy(&args[0].vars->forks[i]);
		i++;
	}
	free(args[0].vars->forks);
	free(args);
}

t_arg	*args_init(t_philo	*vars, unsigned int i)
{
	t_arg			*args;

	args = malloc(vars->total * sizeof(t_arg));
	vars->forks = malloc(vars->total * sizeof(pthread_mutex_t));
	vars->term = malloc(sizeof(pthread_mutex_t));
	vars->is_dead = malloc(sizeof(t_mutex));
	vars->has_all_eaten = malloc(sizeof(t_mutex));
	if (args == NULL || vars->forks == NULL || vars->term == NULL
		|| vars->is_dead == NULL || vars->has_all_eaten == NULL)
		return (NULL);
	pthread_mutex_init(vars->term, NULL);
	pthread_mutex_init(&vars->is_dead->mutex, NULL);
	vars->is_dead->value = 0;
	pthread_mutex_init(&vars->has_all_eaten->mutex, NULL);
	vars->has_all_eaten->value = 0;
	while (i < vars->total)
	{
		pthread_mutex_init(&vars->forks[i], NULL);
		args[i].n = i;
		args[i].has_eaten = 0;
		args[i].vars = vars;
		i++;
	}
	return (args);
}

int	main(int argc, char const *argv[])
{
	t_philo			vars;
	t_arg			*args;

	if (!is_args(argc, argv, &vars))
	{
		printf("Error\n");
		return (0);
	}
	args = args_init(&vars, 0);
	if (args == NULL)
		return (0);
	start_simu(args);
	exit_simu(args);
	return (0);
}
