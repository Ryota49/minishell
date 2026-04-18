# Minishell


*This project has been created as part
of the 42 curriculum by anfouger and jemonthi.*

# Description

Minishell is a 42 project where you have to recreate a shell. You will need a working history, Display a promps when waiting for a new command, search and launch the right executable, 


# Instructions

To compile all the files just run **make** at the root of the repository.

> make

It will create the executable "philo", to test it just type like the example below :

> ./philo 5 4000 200 200

It will create 5 philosophers that should be eating, sleeping and thinking without finishing for this example.

If you wanna test to put 6 args with a number_of_time_each_philosophers_must_eat : 

> ./philo 5 4000 200 200 10

Each philosophers will eat 10 meals before the simulation stops.

You can also check with a low number in time_to_die to see the simulation stops when a philosopher dies like below :

> ./philo 5 400 200 200 10

You can test with any number > 0 and <= INT_MAX, but remember, the higher your number is, the more time it will take to finish the simulation. I recommend you to use with low number and a max of 10000 if you don't wanna wait too long.

# Ressources

Here are some documentations i have read/watched during the project :

- https://man7.org/linux/man-pages/man2/gettimeofday.2.html
- https://youtu.be/mvZKu0DfFLQ?si=m0EfL-oNV_iRMda0
- https://www.ibm.com/docs/fr/aix/7.3.0?topic=programming-using-mutexes
- https://man7.org/linux/man-pages/man3/usleep.3.html
- https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3.html
- https://koor.fr/C/cthreads/Index.wp
- https://www.youtube.com/watch?v=VYPcmMo1sYk