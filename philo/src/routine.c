#include "../include/philo.h"

int	are_they_alive(t_data *d, int id)
{
	if (d->shutdown == 1)
		return (1);
	if ((unsigned long)d->die + d->last_meal_time[id - 1] < current_time(d->start))
	{
		print_action(id, DIED, d->start);
		printf("CURRENT %lu\n", current_time(d->start));
	       	printf("LAST MEAL TIME %lu\n", d->last_meal_time[id - 1]);
	       	printf("TIME TO DIE %lu\n", (unsigned long)d->die);
		d->shutdown = 1;
		return (1);
	}
	return (0);
}

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
}

void	eat_and_drop(t_data *data, int id)
{
	if (data->status[id - 1] != 2 || data->shutdown == 1)
		return ;
	print_action(id, EAT, data->start);
	u_sleep(data->eat, data);
	print_action(id, SLEEP, data->start);
	u_sleep(data->sleep, data);
	pthread_mutex_lock(&data->lock[id - 1]);
	data->forks[id - 1] = 0;
	data->status[id - 1] = 0;
	data->last_meal_time[id - 1] = current_time(data->start);
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
		print_action(philo->id, THINK, philo->data->start);
		u_sleep(philo->data->eat / 2, data);
	}
	while (1)
	{
		if (are_they_alive(philo->data, philo->id) == 1)
			return (NULL);
		ford_pickup(philo->data, philo->id);
		eat_and_drop(philo->data, philo->id);
	}
	return (NULL);
}
