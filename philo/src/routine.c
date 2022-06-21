#include "../include/philo.h"

void	ford_pickup(t_data *data, int id)
{
	int	tmp_id;

	if (data->shutdown == 1)
		return ;
	pthread_mutex_lock(&data->lock[id - 1]);
	if (data->forks[id - 1] == 0)
	{
		data->forks[id - 1] = 1;
		data->status[id - 1] += 1;
		print_action(id, FORK, data);
	}
	pthread_mutex_unlock(&data->lock[id - 1]);
	tmp_id = id;
	if (id == data->size)
		tmp_id = 0;
	pthread_mutex_lock(&data->lock[tmp_id]);
	if (data->forks[tmp_id] == 0)
	{
		data->forks[tmp_id] = 1;
		pthread_mutex_lock(&data->lock[id - 1]);
		data->status[id - 1] += 1;
		pthread_mutex_unlock(&data->lock[id - 1]);
		print_action(id, FORK, data);
	}
	pthread_mutex_unlock(&data->lock[tmp_id]);
}

void	eat_and_drop(t_data *data, int id)
{
	int	save;

	if (data->status[id - 1] != 2 || data->shutdown == 1)
		return ;
	data->time_of_death[id - 1] = current_time() + data->die;
	print_action(id, EAT, data);
	u_sleep(data->eat);
	pthread_mutex_lock(&data->lock[id - 1]);
	data->forks[id - 1] = 0;
	data->status[id - 1] = 0;
	pthread_mutex_unlock(&data->lock[id - 1]);
	save = id;
	if (id == data->size)
		id = 0;
	pthread_mutex_lock(&data->lock[id]);
	data->forks[id] = 0;
	pthread_mutex_unlock(&data->lock[id]);
	print_action(save, SLEEP, data);
	u_sleep(data->sleep);
	print_action(save, THINK, data);
}

void	*routine(void *data)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)data;
	if (philo->id % 2)
	{
		print_action(philo->id, THINK, philo->data);
		u_sleep(philo->data->eat / 2);
	}
	while (1)
	{
		if (philo->data->shutdown == 1)
			return (NULL);
		ford_pickup(philo->data, philo->id);
		usleep(100);
		eat_and_drop(philo->data, philo->id);
		if (death_check(philo, philo->data, philo->id) > 0)
			return (NULL);
	}
	return (NULL);
}
