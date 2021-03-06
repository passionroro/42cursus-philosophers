# Philosophers Dining Problem
## Subject
This project is an introduction to threading and processes, and how to work on the same memory on the same memory space. You will learn how to manipulate threads. You will learn about mutexes, semaphores and shared memory.
## The problem
N philosophers are dining together at the same table with N forks. For the program to run proprerly, each philosopher must take 2 forks, eat and go to sleep. If a philosopher doesn't eat within a certain time, he dies.
### How the code must work
As we must use threads, every philosophers are trying to pick up forks at the same times. Therefore, we must use locks to prevent them from picking two forks at the same time.
### Compiling
`git clone https://github.com/passionroro/42cursus-philosophers.git`\
`cd 42cursus-philosophers/philo`\
Using make to compile :
`make`
Executing the program `./philo` with the following parameters :
- `[nb_of_philo]` : amount of philosophers dining at the table. Must be a positive integer between 1 and 240.
- `[time_to_die]` : if the philosopher hasn't eaten within [time_of_death], he dies.
- `[time_to_eat]` : time it takes for a philo to eat.
- `[time_to_sleep]` : time it takes for a philo to sleep.
- `[must_eat]` : amount of meals. (optionnal)
_example : ./philo 4 500 200 200_

### Understanding my code
In the struct `t_data` you will find the structure of my code, containing : 
- tid : array of thread IDs
- meals : array of meals eaten. init to zero and incremented after every meals.
- time_of_death : array of long int. incremented after every meal. if time_of_death < current_time, the philo has died.
- lock : array of pthread_mutex
- forks : array of int. one if the philo has a fork in its hand. can be left hand or right hand.
- status : number of forks in the hands of a philosopher. if status of a philo is two then he can eat.

#### ROUTINE
```c
	while (1)
	{
		if (philo->data->shutdown == 1)
			return (NULL);
		//try to pick up two forks
		ford_pickup(philo->data, philo->id);
		//if philo->id has 2 forks, he eats, changes his time_of_death and goes to sleep
		eat_and_drop(philo->data, philo->id);
	}
```

#### TRYING TO PICK UP FORKS
```c
    	//locking to avoid multiple philos picking up forks
	pthread_mutex_lock(&data->lock[id - 1]);
	if (data->forks[id - 1] == 0)
	{
		data->forks[id - 1] = 1;
		//picking the fork on his right
		data->status[id - 1] += 1;
		print_action(id, FORK, data);
	}
	pthread_mutex_unlock(&data->lock[id - 1]);
	//don't forget to unlock
```
## Testing ([source](https://github.com/iciamyplant/Philosophers))
| test | expected result??|
|----------|-------|
| ./philo 1 200 200 200 | philo 1 only takes a fork and dies after 200 ms |
| ./philo 2 800 200 200 | nobody dies |
| ./philo 5 800 200 200 | nobody dies |
| ./philo 5 800 200 200 7 | the simulation stops when each philo has eaten 7 times |
| ./philo 4 410 200 200 | nobody dies |
| ./philo 4 310 200 200 | one philo dies |
| ./philo 4 500 200 1.2 | invalid argument |
| ./philo 4 0 200 200 | invalid argument |
| ./philo 4 -500 200 200 | invalid argument |
| ./philo 4 500 200 2147483647 | a philo dies after 500 ms | 
| ./philo 4 -500 200 200 | invalid argument |
| ./philo 4 2147483647 200 200 | nobody dies |
| ./philo 4 214748364732 200 200 | invalid argument|
| ./philo 4 200 210 200 | a philo dies, must show death before 210 ms |


