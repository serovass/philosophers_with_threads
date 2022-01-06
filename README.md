# philosophers_with_threads
**Philosophers with threads and mutex.**

One or more philosophers are sitting at a round table doing one of three things: eating, thinking, or sleeping.  
The philosophers sit at a circular table with a large bowl of spaghetti in the center.  
There are also some forks on the table. The number of forks is equal to the number of philosophers.  
A philosopher must eat with two forks, one for each hand.  
Every philosopher needs to eat.  
Philosophers don’t speak with each other.  
Philosophers don’t know when another philosopher is about to die.  
Each time a philosopher has finished eating, he will drop his forks and start sleeping.  
When a philosopher is done sleeping, he will start thinking.  
The simulation stops when a philosopher dies.  
Each philosopher should be a thread.

**External functions:**
```
malloc
free
write,
usleep
gettimeofday
pthread_create
pthread_detach
pthread_join
pthread_mutex_init
pthread_mutex_destroy
pthread_mutex_lock
pthread_mutex_unlock
```
**Program name:** philo  
**Arguments:**  
number_of_philosophers  
time_to_die mls *(if a philosopher doesn’t start eating ’time_to_die’ mls after starting his last meal it dies)*  
time_to_eat mls  
time_to_sleep mls  
number_of_times_each_philosopher_must_eat *(optional)*

```
$>make
$>./philo 9 300 100 100
```
<img width="1305" alt="9_300_100_100" src="https://user-images.githubusercontent.com/89840597/139281302-c8ca8936-4aff-40ea-947c-5dcb0a5f3d07.png">

