# Minishell


*This project has been created as part
of the 42 curriculum by anfouger, jemonthi.*

# Description

Minishell is a 42 project where you have to recreate a shell. You will need a working history, Display a promps when waiting for a new command, search and launch the right executable.  

**Here are some exemple below of what should work** : 

◦ ctrl-C displays a new prompt on a new line.  
◦ ctrl-D exits the shell.  
◦ ctrl-\ does nothing.  

**Implement the following redirections:**  
◦ < should redirect input.  
◦ > should redirect output.  
◦ << should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!  
◦ >> should redirect output in append mode.  

**Implement pipes (| character). The output of each command in the pipeline is
connected to the input of the next command via a pipe.**  

**Handle environment variables (followed by a sequence of characters) which
should expand to their values.**  

**Handle $? which should expand to the exit status of the most recently executed
foreground pipeline.**  

**The shell must implement the following built-in commands**:  
◦ echo with option -n  
◦ cd with only a relative or absolute path  
◦ pwd with no options  
◦ export with no options  
◦ unset with no options  
◦ env with no options or arguments  
◦ exit with no options  



# Instructions

To compile all the files just run **make** at the root of the repository.

> make

It will create the executable "minishell", to test it just type like the example below :

> ./minishell

You will be inside the shell of minishell, you should see a display promps on the right saying minishell. Now you are ready to test all the command requiered in the subject !

For example, if you want to test a simple builtin of minishell, write inside the minishell :

> echo hi

You are free to do your own test ! you can test pipes, redirections infile/outfile, the builtins...

If you want to leave the minishell, just type :

> exit

you will be back to the main shell.
# Ressources

Here are some documentations we have read/watched during the project (we didn't save all of the website we went tbh):

- https://www.youtube.com/watch?v=IGW8-yeYRgI
- https://codesignal.com/learn/courses/bash-script-error-handling/lessons/understanding-exit-statuses
- https://man7.org/linux/man-pages/man3/errno.3.html

Most of the *man* of the allowed functions has been reviewed too.