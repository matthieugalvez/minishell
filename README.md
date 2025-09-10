# minishell

Minishell is a minimalist Linux shell using environment to find and execute programs, bare a few builtin functions.


## Installation

Use make to build minishell executable binary.

```bash
make
```


## Redirection options

### infile
```
< <infile name> <program>
```
Redirect program's input into infile.

### heredoc
```
<< <EOF> <program>
```
Redirect program's input into a heredoc terminated by <EOF>.

### truncate outfile
```
> <outfile name> <program>
```
Redirect program's output into outfile. Write over pre-existing outfile.

### append outfile
```
>> <outfile name> <program>
```
Redirect program's output into outfile. append at the end of pre-existing outfile.

### pipe
```
<program 1> | <program 2>
```
Pipe the output of <program 1> into the input of <program 2>.


## Builtin functions

### exit
```
exit [exit code]
```
Exit minishell with the last known exit code or the optional [exit code] option.

### pwd
```
pwd
```
Print current working directory of minishell.

### cd
```
cd [path]
```
Move current working directory to [path]. Support both relative and absolute path. If no option is specified, cd try to set current working directory to environment variable "HOME".

### echo
```
echo [-n] <string>
```
Print <string> into standard output followed by a newline. [-n] option escape the terminating newline.

### env
```
env
```
Print current minishell environment.

### export
```
export <variable name>=<attribute>
```
Add the variable with name <variable name> with attribute <attribute> to the minishell environment.

### unset
```
unset <variable name>
```
Remove the variable with name <variable name> from the minishell environment.
