#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>

# define UINT_MAX_STR "4294967295"

typedef struct	s_philo
{
	unsigned int	total;
	unsigned int	n;
	unsigned int	ttd;
	unsigned int	tte;
	unsigned int	tts;
	unsigned int	me;
}	t_philo;

typedef struct s_arg
{
	unsigned int	n;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*term;
	t_philo			vars;
}	t_arg;

int				ft_strcmp(const char *s1, const char *s2);
unsigned int	ft_atoi(const char *nptr);

int				is_args(int argc, char const *argv[], t_philo *vars);

#endif