/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esever <esever@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 02:01:10 by esever            #+#    #+#             */
/*   Updated: 2025/08/30 03:19:09 by esever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->print_lock);
	time = get_current_time() - philo->start_time;
	if (!dead_loop(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->print_lock);
}

void	thinking(t_philo *philo)
{
	print_msg("is thinking", philo, philo->id);
}

void	sleeping(t_philo *philo)
{
	print_msg("is sleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_msg("has taken a fork", philo, philo->id);
	if (philo->nbr_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_msg("has taken a fork", philo, philo->id);
	philo->flag_eat = 1;
	print_msg("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->flag_eat = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
