/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esever <esever@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 02:07:19 by esever            #+#    #+#             */
/*   Updated: 2025/08/30 04:18:25 by esever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_routine(void *ptr_philo)
{
	t_philo	*philo;

	philo = (t_philo *)ptr_philo;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	all_thread_create(t_data *data, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &monitor, data->philos) != 0)
		free_all("Thread creation error", data, forks);
	i = 0;
	while (i < data->philos[0].nbr_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine,
				&data->philos[i]) != 0)
			free_all("Thread creation error", data, forks);
		i++;
	}
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		free_all("Thread join error", data, forks);
	while (i < data->philos[0].nbr_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			free_all("Thread join error", data, forks);
		i++;
	}
	return (0);
}
