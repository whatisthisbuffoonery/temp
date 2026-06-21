*This project has been created as part of the 42 curriculum by dthoo and achew*  
  
## Description  
  
Minishell is an emulation of a small subset of Bash. This subset includes:  
	env variables, not including positional parameters  
	basic working history, not including history expansion  
	execution of binaries, either directly or through PATH  
	echo, pwd, cd, env, export, unset, and exit as builtins  
	handling for SIGINT, SIGQUIT, and ctrl d  
	checking exit status through $?  
	single and double quote handling, except for unclosed quotes  
	redirections: >, >>, <, <<  
	pipelines  
  
The bonus part includes:  
	wildcards for the current directory  
	and conditional execution || &&  
  
## Instructions  
  
Compile in the root directory with
```
make
```
Run the executable without arguments or with --version
```
./minishell
```
  
## Resources  
  
- [The Bash Manual](https://www.gnu.org/software/bash/manual/html_node/index.html#SEC_Contents)  
- [Darren's pipex README for pipeline and PATH semantics without considering signals](https://github.com/whatisthisbuffoonery/temp/blob/main/uwu/pipex/README.md)  
- Pipeline behaviour under signals: I think this was in the bash manual somewhere, but it is quite vague. We tested everything manually.  
- [Behaviour of export with no args, cd, pwd, and unset](https://man7.org/linux/man-pages/man1/bash.1.html#:~:text=SHELL%20BUILTIN%20COMMANDS%20%C2%A0): way way down in the man page for Bash, starting at around line 2500.  
- [Behaviour of env with no args](https://www.gnu.org/savannah-checkouts/gnu/coreutils/manual/html_node/env-invocation.html): 'info env' will show the relevant documentation.  
- [Behaviour of exit](https://man7.org/linux/man-pages/man1/exit.1p.html)  
- [Basic signal semantics](https://beej.us/guide/bgc/html/split-wide/signal-handling.html#signal-handling)  
- AI was used in various places for refactoring, squeezing ioctl and the termios functions into the picture, and finding silly semantic errors.  
