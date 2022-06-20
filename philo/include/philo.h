#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# define THINK "is thinking"
# define FORK "has taken a fork"
# define EAT "is eating"
# define DIED "died"
# define SLEEP "is sleeping"

enum	e_rror
{
	ERR_THREAD = 1,
	ERR_JOIN,
	ERR_MALLOC,
	ERR_MUTEX,
};

typedef struct s_data 
{
	int				size;
	int				die;
	int				eat;
	int				sleep;
	int				must_eat;
	long			start;
	int				shutdown;
	int				*forks;
	int				*status;
	pthread_mutex_t	*lock;
	pthread_mutex_t	print;
	pthread_t		*tid;
}			t_data;

typedef struct s_philosophers 
{
	int			id;
	int			nb_eat;
	long		time_of_death;
	t_data		*data;
}		t_philosophers;

void	*routine(void *data);
void	ford_pickup(t_data *data, int id);
void	eat_and_drop(t_data *data, t_philosophers *philo, int id);
int		are_they_alive(t_philosophers *p, t_data *d, int id);
int		var_init(t_data *d, char **argv, int argc);
int		data_init(t_data *data, t_philosophers *philo);
int		philo_init(t_data *data, t_philosophers *philo);
void	print_action(int num, char *status, t_data *data);
int		ft_atoi(const char *str);
long 	current_time(void);
void	u_sleep(long time);
void	*destroy_philo(t_data *data, int id);
int		ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, int n);
int	death_monitor(t_philosophers *philo, t_data *data);
void	clean_threads(t_data *data);

#endif
