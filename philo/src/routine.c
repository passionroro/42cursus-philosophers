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
		data->status[id - 1] += 1;
		print_action(id, FORK, data);
	}
	pthread_mutex_unlock(&data->lock[tmp_id]);
	usleep(100);
}

void	eat_and_drop(t_data *data, t_philosophers *philo, int id)
{
	if (data->status[id - 1] != 2 || data->shutdown == 1)
		return ;
	if (data->must_eat != -1)
		philo->nb_eat += 1;
	pthread_mutex_lock(&data->death[id - 1]);
	data->time_of_death[id - 1] = current_time() + data->die;
	pthread_mutex_unlock(&data->death[id - 1]);
	print_action(id, EAT, data);
	u_sleep(data->eat);
	print_action(id, SLEEP, data);
	u_sleep(data->sleep);
	pthread_mutex_lock(&data->lock[id - 1]);
	data->forks[id - 1] = 0;
	data->status[id - 1] = 0;
	pthread_mutex_unlock(&data->lock[id - 1]);
	if (id == data->size)
		id = 0;
	pthread_mutex_lock(&data->lock[id]);
	data->forks[id] = 0;
	pthread_mutex_unlock(&data->lock[id]);
}

void	*routine(void *data)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)data;
	if (!(philo->id % 2))
	{
		print_action(philo->id, THINK, philo->data);
		u_sleep(philo->data->eat / 2);
	}
	while (1)
	{
		if (philo->data->shutdown == 1)
			return (NULL);
		ford_pickup(philo->data, philo->id);
		eat_and_drop(philo->data, philo, philo->id);
		if (death_check(philo, philo->data, philo->id) > 0)
			return (NULL);
	}
	return (NULL);
}
