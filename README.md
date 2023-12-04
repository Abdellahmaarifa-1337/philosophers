# Philosophers - I never thought philosophy would be so deadly

## Introduction

Philosophers is a project designed to teach the basics of threading a process, focusing on creating threads and using mutexes. The simulation involves philosophers sitting at a round table, eating, thinking, and sleeping. The project includes a mandatory part (using threads and mutexes) and a bonus part (using processes and semaphores).

## Common Instructions

- Written in C.
- Norm compliance is mandatory.
- Functions should not quit unexpectedly (except for undefined behaviors).
- Free all heap-allocated memory properly; no leaks.
- Include a Makefile.
- Makefile must compile with flags -Wall, -Wextra, and -Werror.
- Makefile must include rules $(NAME), all, clean, fclean, and re.
- If applicable, include a bonus rule in the Makefile for bonus functions.
- If libft is allowed, copy its sources and Makefile into a libft folder.
- Encouraged to create test programs for the project, although not graded.
- Submit work to the assigned Git repository.

## Overview

- Philosophers sit at a round table with a bowl of spaghetti.
- They alternate between eating, thinking, and sleeping.
- Forks are placed on the table; each philosopher needs two forks to eat.
- Philosophers don't speak with each other.
- No communication about a philosopher's impending death.
- Philosophers must avoid starvation.

## Global Rules

- Two programs: one for the mandatory part (philo) and one for the bonus part (philo_bonus).
- Arguments: `number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`
- Philosophers numbered from 1 to `number_of_philosophers`.
- Log format for state changes: `timestamp_in_ms X action`.
- No data races allowed.

## Mandatory Part

### Program: philo

- Files: Makefile, _.h, _.c, in the directory philo/
- Arguments: `number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`
- External Functions: memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
- Libft Authorized: No
- Description: Philosophers with threads and mutexes

## Bonus Part

### Program: philo_bonus

- Files: Makefile, _.h, _.c, in the directory philo_bonus/
- Arguments: `number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`
- External Functions: memset, printf, malloc, free, write, fork, kill, exit, pthread_create, pthread_detach, pthread_join, usleep, gettimeofday, waitpid, sem_open, sem_close, sem_post, sem_wait, sem_unlink
- Libft Authorized: No
- Description: Philosophers with processes and semaphores
