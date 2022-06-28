/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 11:32:28 by rohoarau          #+#    #+#             */
/*   Updated: 2022/06/28 11:32:29 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	u_sleep(long time)
{
	long	start;

	start = current_time();
	while (current_time() - start < time)
		usleep(100);
}

void	print_action(int num, char *status, t_data *data)
{
	static int	shutdown = 0;

	pthread_mutex_lock(&data->print);
	if (shutdown == 1)
		return ;
	if (!ft_strncmp(status, DIED, ft_strlen(status)))
		shutdown = 1;
	printf("%ld\t %d %s\n", current_time() - data->start, num, status);
	pthread_mutex_unlock(&data->print);
}
