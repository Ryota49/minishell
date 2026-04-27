*This project has been created as part
of the 42 curriculum by anfouger, jemonthi.*
# Minishell

## Description

**Minishell** is a project from the 42 curriculum where the goal is to recreate a simplified version of a Unix shell, similar to [Bash](https://en.wikipedia.org/wiki/Bash_%28Unix_shell%29).

A shell is a program that allows users to interact with the operating system by typing commands. Instead of using a graphical interface, you communicate directly with the system through text instructions. For example, commands like `ls`, `cd`, or `echo` are interpreted and executed by the shell.

### What is a shell?

A [shell](https://en.wikipedia.org/wiki/Unix_shell) is essentially a command interpreter. It takes user input, processes it, and executes the corresponding programs. It also provides features such as:

* launching executables
* managing processes
* handling input/output redirections
* connecting commands with pipes
* expanding environment variables

Minishell reproduces these core behaviors to help understand how a real shell like Bash works internally.

---

In this project, we implemented a functional shell capable of:

* displaying a prompt and handling user input
* maintaining a command history
* searching and executing binaries from the system
* handling signals (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`)

### Supported features

**Redirections:**

* `<` redirect input
* `>` redirect output
* `>>` append output
* `<<` heredoc (read input until a delimiter)

**Pipes:**

* `|` connects the output of one command to the input of another

**Environment variables:**

* `$VAR` expands to its value
* `$?` returns the last command exit status

**Builtins:**

* `echo` with `-n`
* `cd` with relative or absolute path
* `pwd`
* `export`
* `unset`
* `env`
* `exit`

---

Minishell is not just about reproducing features it is about understanding **how a shell interprets, transforms, and executes commands step by step**.

Internally, the program is structured in several stages:

* **Input handling** using `readline`
* **Tokenization**: splitting the input into meaningful elements (commands, pipes, redirections…)
* **Parsing**: organizing tokens into a structured representation of the command
* **Execution**:

  * launching builtins directly
  * or creating child processes with `fork` + `execve`
* **File descriptor management** for pipes and redirections

This pipeline reflects how real shells process user commands under the hood.

---

## Instructions

To compile the project, run:

```bash
make
```

This will generate the executable:

```bash
./minishell
```

Additional commands:

```bash
make clean      # remove object files
make fclean     # remove objects + executable
make re         # rebuild everything
```

---

Once launched, you will see the Minishell prompt.
You can now execute commands just like in a standard shell.

Example:

```bash
echo hello
```

Try more advanced features:

```bash
ls | grep .c
```

```bash
echo hello > file.txt
```

```bash
cat < file.txt
```

To exit the shell:

```bash
exit
```

---

## Ressources

Here are some documentations we have read/watched during the project (we didn't save all of the website we went tbh):

- [GDB Debugging with fork() and exec() - Jacob Sorber - Youtube](https://www.youtube.com/watch?v=IGW8-yeYRgI)
- [Course on Bash script error handling - CodeSignal](https://codesignal.com/learn/courses/bash-script-error-handling/lessons/understanding-exit-statuses)
- [errno(3) - Linux manual page](https://man7.org/linux/man-pages/man3/errno.3.html)
- [Comprehensive guide on lexer and parsing - Flash - Medium](https://medium.com/@august1.caes/minishell-a-comprehensive-guide-24cb30a342ec)

AI was used to explain a new concept and speed up the debugging process. It was also used for the README.

Most of the `man` of the allowed functions has been reviewed too.