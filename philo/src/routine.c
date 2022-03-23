#include "../include/philo.h"

void	ford_pickup(t_philosophers *philo, t_data *data, int id)
{
	pthread_mutex_lock(&data->lock[id]);
	if (data->forks[id] == 0)
	{
		data->forks[id] = 1;
		print_action(id, FORK, data->start);
	}
	pthread_mutex_unlock(&data->lock[id]);
	pthread_mutex_lock(&data->lock[(id + 1) % data->size]);
	if (data->forks[(id + 1) % data->size] == 0)
	{
		data->forks[(id + 1) % data->size] = 1;
		print_action(id, FORK, data->start);
	}
	pthread_mutex_unlock(&data->lock[(id + 1) % data->size]);
	if (data->forks[(id + 1) % data->size] == 1 && data->forks[id] == 1)
	{
		print_action(id, EAT, data->start);
		usleep(data->eat * 1000);
		pthread_mutex_lock(&data->lock[id]);
		data->forks[id] = 0;
		pthread_mutex_unlock(&data->lock[id]);
		pthread_mutex_lock(&data->lock[(id + 1) % data->size]);
		data->forks[(id + 1) % data->size] = 0;
		pthread_mutex_unlock(&data->lock[(id + 1) % data->size]);
		philo->nb_eat++;
	}
}
/*
int	eat_and_drop(t_philosophers *philo, t_data *data, int id)
{
	return (0);
}*/

void	*routine(void *data)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)data;
	if (philo->id % 2)
		sleep(200);
	while (1)
		ford_pickup(philo, philo->data, philo->id);
	return (NULL);
}
