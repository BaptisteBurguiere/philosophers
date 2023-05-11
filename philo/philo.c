#include "philo.h"

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

void	*philo_ttd(void *data)
{
	t_ttd_mutex	*ttd_mutex;

	ttd_mutex = (t_ttd_mutex *) data;
	while (1)
	{
		usleep(1000);
		pthread_mutex_lock(&ttd_mutex->mutex);
		ttd_mutex->ttd -= 1;
		if (ttd_mutex->ttd <= 0)
		{
			pthread_mutex_lock(ttd_mutex->term);
			printf("%lld %u died\n", get_time(), ttd_mutex->n + 1);
			pthread_mutex_unlock(ttd_mutex->term);
			*ttd_mutex->is_dead = 1;
			pthread_mutex_unlock(&ttd_mutex->mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&ttd_mutex->mutex);
	}
}

void	*philo_routine(void *data)
{
	t_arg			*arg;
	t_ttd_mutex		ttd_mutex;
	pthread_t		ttd_thread;

	arg = (t_arg *) data;
	pthread_mutex_init(&ttd_mutex.mutex, NULL);
	ttd_mutex.ttd = arg->vars.ttd;
	ttd_mutex.is_dead = arg->is_dead;
	ttd_mutex.term = arg->term;
	ttd_mutex.n = arg->n;
	pthread_create(&ttd_thread, NULL, philo_ttd, &ttd_mutex);
	while (1)
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
		usleep(arg->vars.tte * 1000);

		if (arg->n == 0)
			pthread_mutex_unlock(&arg->forks[arg->vars.total - 1]);
		else
			pthread_mutex_unlock(&arg->forks[arg->n - 1]);
		pthread_mutex_unlock(&arg->forks[arg->n]);

		pthread_mutex_lock(&ttd_mutex.mutex);
		ttd_mutex.ttd = arg->vars.ttd;
		pthread_mutex_lock(arg->term);
		printf("%lld %u is sleeping\n", get_time(), arg->n + 1);
		pthread_mutex_unlock(arg->term);
		usleep(arg->vars.tts * 1000);
		pthread_mutex_unlock(&ttd_mutex.mutex);

		pthread_mutex_lock(arg->term);
		printf("%lld %u is thinking\n", get_time(), arg->n + 1);
		pthread_mutex_unlock(arg->term);
	}
	return (NULL);
}

void	start_simu(t_arg *args, unsigned int nb)
{
	pthread_t		*philos;
	unsigned int	i;

	philos = malloc(nb * sizeof(pthread_t));
	if (philos == NULL)
		return ;
	i = 0;
	get_time();
	while(i < nb)
	{
		pthread_create(&philos[i], NULL, philo_routine, &args[i]);
		usleep(50000);
		i++;
	}
	while (*args[0].is_dead == 0)
	{}
}

t_arg	*args_init(t_philo vars)
{
	t_arg			*args;
	pthread_mutex_t *forks;
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
	while (i < vars.total)
	{
		args[i].term = term;
		args[i].forks = forks;
		args[i].n = i;
		args[i].vars = vars;
		args[i].is_dead = is_dead;
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (args);
}

int main(int argc, char const *argv[])
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
	return 0;
}