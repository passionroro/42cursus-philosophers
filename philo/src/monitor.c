#include "../include/philo.h"

int	monitor_meals(t_data *data, int i)
{
	if (data->meals[i] <= data->must_eat)
		return (0);
	data->shutdown = 1;
	return (1);
}

int	death_check(t_data *data)
{
	int		i;
	long	time;

	while (1)
	{
		i = -1;
		time = current_time();
		while (++i < data->size)
		{
			if (data->time_of_death[i] < time)
			{
				print_action(i + 1, DIED, data);
				data->shutdown = 1;
				return (1);
			}
			if (data->must_eat != -1)
				if (monitor_meals(data, i) == 1)
					return (2);
		}
	}
	return (0);
}
