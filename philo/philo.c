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

void	start_simu(t_arg *args, unsigned int nb)
{
	pthread_t		*philos;
	unsigned int	i;

	philos = malloc(nb * sizeof(pthread_t));
	if (philos == NULL)
		return ;
	i = 0;
	get_time();
	while (i < nb)
	{
		pthread_create(&philos[i], NULL, philo_routine, &args[i]);
		i++;
	}
	while (*args[0].is_dead == 0)
	{
	}
	i = 0;
	while (i < nb)
	{
		pthread_mutex_destroy(&args->forks[i]);
		i++;
	}
	free(args->forks);
	pthread_mutex_destroy(args->term);
	free(args->term);
	free(args->is_dead);
	free(args);
}

t_arg	*args_init(t_philo vars)
{
	t_arg			*args;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*term;
	int				*is_dead;
	unsigned int	i;

	forks = malloc(vars.total * sizeof(pthread_mutex_t));
	term = malloc (sizeof(pthread_mutex_t));
	args = malloc(vars.total * sizeof(t_arg));
	is_dead = malloc(sizeof(int));
	if (args == NULL || forks == NULL || term == NULL || is_dead == NULL)
		return (NULL);
	pthread_mutex_init(term, NULL);
	*is_dead = 0;
	i = 0;
	while (i++ < vars.total)
	{
		args[i - 1].term = term;
		args[i - 1].forks = forks;
		args[i - 1].n = i - 1;
		args[i - 1].vars = vars;
		args[i - 1].is_dead = is_dead;
		pthread_mutex_init(&forks[i - 1], NULL);
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
	args = args_init(vars);
	if (args == NULL)
		return (0);
	start_simu(args, vars.total);
	return (0);
}
