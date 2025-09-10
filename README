# minishell

Minishell is a minimalist Linux shell using environment to find and execute programs, bare a few builtin functions.


## Installation

Use make to build minishell executable binary.

```bash
make
```


## Redirection options

# infile
```bash
< <infile name> <program>
```
Redirect program's input into infile.

# heredoc
```bash
<< <EOF> <program>
```
Redirect program's input into a heredoc terminated by <EOF>.

# truncate outfile
```bash
> <outfile name> <program>
```
Redirect program's output into outfile. Write over pre-existing outfile.

# append outfile
```bash
>> <outfile name> <program>
```
Redirect program's output into outfile. append at the end of pre-existing outfile.

# pipe
```bash
<program 1> | <program 2>
```
Pipe the output of <program 1> into the input of <program 2>.


## Builtin functions

# exit
```bash
exit [exit code]
```
Exit minishell with the last known exit code or the optional [exit code] option.

# pwd
```bash
pwd
```
Print current working directory of minishell.

# cd
```bash
cd [path]
```
Move current working directory to [path]. Support both relative and absolute path. If no option is specified, cd try to set current working directory to environment variable "HOME".
