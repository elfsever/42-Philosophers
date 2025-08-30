/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esever <esever@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 02:36:23 by esever            #+#    #+#             */
/*   Updated: 2025/08/30 04:16:03 by esever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philo_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= time_to_die
		&& philo->flag_eat == 0)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].nbr_philos)
	{
		if (is_philo_dead(&philos[i], philos[i].time_to_die))
		{
			print_msg("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_all_ate(t_philo *philos)
{
	int	i;
	int	count_eating;

	i = 0;
	count_eating = 0;
	if (philos[0].must_eaten == -1)
		return (0);
	while (i < philos[0].nbr_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].must_eaten)
			count_eating++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (count_eating == philos[0].nbr_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *ptr_philo)
{
	t_philo	*philos;

	philos = (t_philo *)ptr_philo;
	while (1)
		if (check_dead(philos) == 1 || check_if_all_ate(philos) == 1)
			break ;
	return (NULL);
}
