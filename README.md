<h1 align="center">
	🍝 Philosophers
</h1>

## 💡 About the project

This project is about learning how threads work by precisely timing a group of philosophers on when to pick up forks and eat spaghetti without dying from hunger.

## Overview

- One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table.
- The philosophers alternatively eat, think, or sleep. While they are eating, they are not thinking nor sleeping; while thinking, they are not eating nor sleeping; and, of course, while sleeping, they are not eating nor thinking.
- There are also forks on the table. There are as many forks as philosophers.
- Because serving and eating spaghetti with only one fork is very inconvenient, a philosopher takes their right and their left forks to eat, one in each hand.
- When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation.
- Every philosopher needs to eat and should never starve.
- Philosophers don’t speak with each other.
- Philosophers don’t know if another philosopher is about to die.
- No need to say that philosophers should avoid dying!


## 📝 Requirements

**Global Rules:**
You have to write a program for the mandatory part and another one for the bonus part. They both have to comply with the following rules:
- Global variables are forbidden!
- Your(s) program(s) should take the following arguments: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
  - number_of_philosophers: The number of philosophers and also the number of forks.
  - time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
  - time_to_eat (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
  - time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
  - number_of_times_each_philosopher_must_eat (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.
- Each philosopher has a number ranging from 1 to number_of_philosophers.
- Philosopher number 1 sits next to philosopher number number_of_philosophers. Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.

**About the logs of your program:**
- Any state change of a philosopher must be formatted as follows:
  - timestamp_in_ms X has taken a fork
  - timestamp_in_ms X is eating
  - timestamp_in_ms X is sleeping
  - timestamp_in_ms X is thinking
  - timestamp_in_ms X died
  - Replace timestamp_in_ms with the current timestamp in milliseconds and X with the philosopher number.
- A displayed state message should not be mixed up with another message.
- A message announcing a philosopher died should be displayed no more than 10 ms after the actual death of the philosopher.
- Again, philosophers should avoid dying!


**Mandatory Rules:**

The specific rules for the mandatory part are:
- Each philosopher should be a thread.
- There is one fork between each pair of philosophers. Therefore, if there are several philosophers, each philosopher has a fork on their left side and a fork on their right side. If there is only one philosopher, there should be only one fork on the table.
- To prevent philosophers from duplicating forks, you should protect the forks state with a mutex for each of them.

**Bonus Rules:**

The specific rules for the bonus part are:
- All the forks are put in the middle of the table.
- They have no states in memory but the number of available forks is represented by a semaphore.
- Each philosopher should be a process. But the main process should not be a philosopher.

## 📋 Testing

To compile, navigate to the project directory and run:

```shell
$ make 
```

Then, execute the program with the following arguments:

```shell
$ ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] *

* optional and last parameter: [number_of_times_each_philosopher_must_eat]
** times are in milliseconds (ms)
```
