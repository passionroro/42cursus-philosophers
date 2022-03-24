#include "../include/philo.h"

void	ford_pickup(t_philosophers *philo, t_data *data, int id)
{
	int	tmp_id;

	pthread_mutex_lock(&data->lock[id - 1]);
	if (data->forks[id - 1] == 0)
	{
		data->forks[id - 1] = 1;
		data->status[id - 1] += 1;
		print_action(id, FORK, data->start);
	}
	pthread_mutex_unlock(&data->lock[id - 1]);
	tmp_id = id;
	if (id == data->size)
		tmp_id = 0;
	pthread_mutex_lock(&data->lock[tmp_id]);
	if (data->forks[tmp_id] == 0)
	{
		data->forks[tmp_id] = 1;
		data->status[id - 1] += 1;
		print_action(id, FORK, data->start);
	}
	pthread_mutex_unlock(&data->lock[tmp_id]);
	if (data->status[id - 1] == 2)
	{
		print_action(id, EAT, data->start);
		usleep(data->eat * 1000);
		pthread_mutex_lock(&data->lock[id - 1]);
		data->forks[id - 1] = 0;
		data->status[id - 1] = 0;
		pthread_mutex_unlock(&data->lock[id - 1]);
		if (id == data->size)
			id = 0;
		pthread_mutex_lock(&data->lock[id]);
		data->forks[id] = 0;
		pthread_mutex_unlock(&data->lock[id]);
		print_action(id, SLEEP, data->start);
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
	if (philo->id % 2 != 0)
	{
		usleep(philo->data->eat * 1000);
		print_action(philo->id, THINK, data->start);
	}
	while (1)
		ford_pickup(philo, philo->data, philo->id);
	return (NULL);
}
