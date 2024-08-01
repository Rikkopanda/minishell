# 42-minishell

The objective of this project is to create a simple shell, like an own little bash.
It is the first group project at Codam college (42 core curriculum).
Group: @ILeXeIR and @Rikkopanda

## Project specifications

A shell is a program which a user can interactively run programs, open/read files and write/append to files.
## Features
### Basics:
- History of previous entered commands
- Search and launch the right executable (based on the PATH variable, using a relative or an absolute path)
- Environment variables ($ followed by a sequence of characters) expand to their values
- Wildcards * in the current working directory
- ctrl-C, ctrl-D and ctrl-\ behave like in bash
- ```’``` (single quotes - prevent from interpreting meta-characters in quoted sequence)
- ```"``` (double quotes - prevent from interpreting meta-characters in quoted sequence except for $)
- ```$?``` expands to the last exit status
- ```|``` connect cmds or groups with pipes; output of a cmd is connected to the input of the next cmd via a pipe
- ```&&``` and ```||``` with parenthesis for priorities
- 
### Builtins:
- ```echo``` with option -n
- ```cd``` (relative or absolute path, ```-``` for OLDPWD, without arg for HOME)
- ```pwd``` without options
- ```export``` without options
- ```unset``` without options
- ```env``` without options
- ```exit [exit_status]``` without options

### Redirections:

```[n]``` (optional) specifies the file descriptor, if not specified it is stdout/stdin

- ```[n]< file``` Redirecting Input
- ```[n]<< limiter``` Here Documents
- ```[n]> file``` Redirecting Output
- ```[n]>> file``` Appending Redirected Output

## How to use

The current version of minishell is developed and tested on linux.

```
git clone git@github.com:Rikkopanda/minishell.git minishell
```
```

cd Libft

git submodule update --init --recursive

git checkout tags/minishell_1
```
```
cd ../minishell && make
```
```
./minishell
```
run commands, programs, do anything you want as you would in bash(some limitations ofcourse)
## Dependencies
### Install readline
```
sudo apt-get install libreadline-dev

```
