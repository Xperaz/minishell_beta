# Minishell
<<<<<<< HEAD
Minishell is a Unix-like shell written in [C]inspired by [Bash](https://en.wikipedia.org/wiki/Bash_(Unix_shell)).

## Content
- (#features)
- (#brief-summary) 

# Features

### Pipes `|` 
```bash
$> cat /etc/passwd | cut -d':' -f1 | sort | uniq # get unique user's
```

### I/O Redirections (`<`, `<<`, `>` and `>>`)
```bash
$> cat << "EOF" > outfile ; < infile cat >> outfile
```

### Built-in Commands
```bash
echo	# Write arguments to the standard output.
cd	# Change the shell working directory.
pwd 	# Print the name of the current working directory.
export 	# Set export attribute for shell variables.
unset 	# Unset values and attributes of shell variables.
env 	# Set environment and execute command, or print environment.
exit	# Exit the shell.
```

# Brief Summary
Before getting any input, we first have to handle Ctrl-C, Ctrl-D, Ctrl-Z and ctrl-\ which should behave like in bash. After that, the program is continuously prompting for a new `command line` input.\
This `command line` goes through many phases before being executed and showing the result.\
First it goes through a LEXER, which splits the input into a "valid" list of tokens. Second, the PARSER. present List of commands. And last but not the least, the EXCUTOR walks this list and executes each node accordingly.
=======
Minishell is a Unix-like shell written in [C] inspired by [Bash](https://en.wikipedia.org/wiki/Bash_(Unix_shell)).
>>>>>>> 67325ddc081eec2fa451f28599c87fa2ad85fdbe
