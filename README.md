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
< <infile> <program>
```
Redirect \<program>'s input into \<infile>.

### heredoc
```
<< <EOF> <program>
```
Redirect \<program>'s input into a heredoc terminated by \<EOF>.

### truncate outfile
```
> <outfile> <program>
```
Redirect \<program>'s output into \<outfile>. Write over pre-existing outfile.

### append outfile
```
>> <outfile> <program>
```
Redirect \<program>'s output into \<outfile>. append at the end of pre-existing outfile.

### pipe
```
<program1> | <program2>
```
Pipe the output of \<program1> into the input of \<program2>.


## Builtin functions

### exit
```
exit [exitCode]
```
Exit minishell with the last known exit code or the optional [exitCode] option.

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
Print \<string> into standard output followed by a newline. [-n] option escape the terminating newline.

### env
```
env
```
Print current minishell environment.

### export
```
export <name>=<attribute>
```
Add the variable with name \<name> with attribute \<attribute> to the minishell environment.

### unset
```
unset <name>
```
Remove the variable with name \<name> from the minishell environment.
