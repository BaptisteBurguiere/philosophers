#include "philo.h"

void	*philo_routine(void *data)
{
	t_arg	*arg;

	arg = (t_arg *) data;
	arg->vars.n = arg->n;
	pthread_mutex_lock(arg->term);
	usleep(200000);
	printf("le philosophe %u est assis a la table.\n", arg->vars.n + 1);
	pthread_mutex_unlock(arg->term);
	return (NULL);
}

t_arg	*args_init(t_philo vars)
{
	t_arg			*args;
	pthread_mutex_t *forks;
	pthread_mutex_t	*term;
	unsigned int	i;

	forks = malloc(vars.total * sizeof(pthread_mutex_t));
	term = malloc (sizeof(pthread_mutex_t));
	args = malloc(vars.total * sizeof(t_arg));
	if (args == NULL || forks == NULL || term == NULL)
		return (NULL);
	pthread_mutex_init(term, NULL);
	i = 0;
	while (i < vars.total)
	{
		args[i].term = term;
		args[i].forks = forks;
		args[i].n = i;
		args[i].vars = vars;
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (args);
}

int main(int argc, char const *argv[])
{
	t_philo			vars;
	pthread_t		*philos;
	unsigned int	i;
	t_arg			*args;

	if (!is_args(argc, argv, &vars))
	{
		printf("Error\n");
		return (0);
	}
	args = args_init(vars);
	if (args == NULL)
		return (0);
	philos = malloc(vars.total * sizeof(pthread_t));
	i = 0;
	while(i < vars.total)
	{
		pthread_create(&philos[i], NULL, philo_routine, &args[i]);
		i++;
	}
	while(1)
	{}
	return 0;
}