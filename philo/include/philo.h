#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

enum	e_rror
{
	ERR_THREAD = 1,
	ERR_JOIN,
	ERR_MALLOC,
	ERR_MUTEX,
};

enum	e_status 
{
	FORK = 0,
	DIED,
	THINK,
	SLEEP,
	EAT,
};

typedef struct s_data 
{
	int		size;
	int		die;
	int		eat;
	int		sleep;
	int		must_eat;
	unsigned long	start;
	int		*forks;
	unsigned long	*last_meal_time;
	int		shutdown;
	int		*status;
	pthread_mutex_t	*lock;
	pthread_mutex_t	stdout_lock;
	pthread_t	*tid;
}			t_data;

typedef struct s_philosophers 
{
	int		id;
	int		nb_eat;
	t_data		*data;
}		t_philosophers;

void	*routine(void *data);
void	ford_pickup(t_data *data, int id);
void	eat_and_drop(t_data *data, int id);
int	are_they_alive(t_data *d, int id);
int	var_init(t_data *d, char **argv, int argc);
int	data_init(t_data *data, t_philosophers *philo);
int	philo_init(t_data *data, t_philosophers *philo);
void	print_action(int num, int status, unsigned long start);
int	ft_atoi(const char *str);
unsigned long 	current_time(unsigned long start);
void	u_sleep(unsigned long time, t_data *data);
void	*destroy_philo(t_data *data, int id);


#endif
