/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bburguie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:10:44 by bburguie          #+#    #+#             */
/*   Updated: 2023/05/12 19:10:45 by bburguie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

# define MAX "4294967295"

// typedef struct s_arg
// {
// 	unsigned int	n;
// 	pthread_mutex_t	*forks;
// 	pthread_mutex_t	*term;
// 	int				*is_dead;
// 	int				has_eaten;
// 	t_philo			vars;
// }	t_arg;

// typedef struct s_ttd_mutex
// {
// 	unsigned int	ttd;
// 	pthread_mutex_t	mutex;
// 	int				*is_dead;
// 	pthread_mutex_t	*term;
// 	unsigned int	n;
// }	t_ttd_mutex;

typedef struct s_mutex
{
	unsigned int	value;
	pthread_mutex_t	mutex;
}	t_mutex;

typedef struct s_philo
{
	unsigned int	total;
	unsigned int	ttd;
	unsigned int	tte;
	unsigned int	tts;
	unsigned int	me;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*term;
	t_mutex			*is_dead;
	t_mutex			*has_all_eaten;
}	t_philo;

typedef struct s_arg
{
	unsigned int	n;
	unsigned int	has_eaten;
	t_mutex			ttd_mutex;
	t_philo			*vars;
}	t_arg;

int				ft_strcmp(const char *s1, const char *s2);
unsigned int	ft_atoi(const char *nptr);
long long		get_time(void);
void			ft_print(t_arg *arg, const char *mess, long long time);

int				is_args(int argc, char const *argv[], t_philo *vars);

void			*philo_routine(void *data);
int				is_over(t_arg *arg);
void			*philo_ttd(void *data);
int				split_1(t_arg *arg);
int				split_2(t_arg *arg);
int				split_3(t_arg *arg);

#endif
