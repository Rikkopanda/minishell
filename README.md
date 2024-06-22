# 42-minishell

The objective of this project is to create a simple shell, like an own little bash.
It is the first group project at Codam college (42 core curriculum).

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

The current version of minishell is developed and tested on linux and macos.

```
git clone git@github.com:Rikkopanda/minishell.git minishell
```
```
cd minishell && make
```
```
./minishell
```
run commands, programs, do anything you want as you would in bash(some limitations ofcourse)
## Dependencies
### Install readline with [brew](https://brew.sh/)
```
brew install readline
```
```
brew link --force readline
```
Add the path to the lib

Replace ~/.zshrc with ~/.bashrc if you use bash instead of zsh
```
echo 'export C_INCLUDE_PATH="/usr/local/opt/readline/include:$C_INCLUDE_PATH"' >> ~/.zshrc
```
```
echo 'export LIBRARY_PATH="/usr/local/opt/readline/lib:$LIBRARY_PATH"' >> ~/.zshrc
```
```
source ~/.zshrc
```

### Install readline on 42 Macs

Install Brew, <b>only if it is not already installed:</b>

```
rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update
```

Install Readline library:
```
brew install readline
```

```
brew link --force readline
```

```
echo 'export C_INCLUDE_PATH="$HOME/.brew/include:$C_INCLUDE_PATH"' >> ~/.zshrc
```

```
echo 'export LIBRARY_PATH="$HOME/.brew/lib:$LIBRARY_PATH"' >> ~/.zshrc
```
```
source ~/.zshrc
```

## Run tests

To check if your minishell build was succesful you can run a tester, which compares most of the features with your current Bash installation. The test compares the stdout and the exit-code directly and checks in case of an error if both print something in stderr. 

```
make test
```

## Activate debug mode

Enter minishell and export the DEBUG env:


## Learning experience/conclusion
It was a great challenge building this project, it took 3 months to complete it.
During this project I learned about working in a team of 2 on a big project.


```
export DEBUG=printer
```

For all next commands you will execute in the minishell you will see the different processing steps from the lexer and parser with syntax highlighting.

