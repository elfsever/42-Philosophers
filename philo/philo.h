/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esever <esever@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 01:31:13 by esever            #+#    #+#             */
/*   Updated: 2025/08/30 04:16:33 by esever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				flag_eat;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				nbr_philos;
	int				must_eaten;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_data
{
	int				flag_dead;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	print_lock;
	t_philo			*philos;
}					t_data;

int		is_numeric(char *arg);
int		check_args(char **argv);
int		ft_atoi(const char *str);
int		ft_strlen(char *str);
int		ft_usleep(size_t ms);
int		dead_loop(t_philo *philo);
int		check_dead(t_philo *philos);
int		check_if_all_ate(t_philo *philos);
int		all_thread_create(t_data *data, pthread_mutex_t *forks);
int		is_philo_dead(t_philo *philo, size_t time_to_die);
void	free_all(char *str, t_data *data, pthread_mutex_t *forks);
void	init_input(t_philo *philo, char **argv);
void	*philo_routine(void *ptr_philo);
void	*monitor(void *ptr_philo);
void	print_msg(char *str, t_philo *philo, int id);
void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);
void	eating(t_philo *philo);
void	init_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks,
			char **argv);
void	init_forks(pthread_mutex_t *forks, int philo_num);
void	init_data(t_data *data, t_philo *philos);
size_t	get_current_time(void);

#endif
