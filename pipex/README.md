*This project has been created as part of the 42 curriculum by dthoo*  
  
##Description  
  
Pipex aims to emulate file redirection as seen in the shell, taking zsh and bash for reference.  
You may recognise some of the symbols below:  
```
< in cmd1 | cmd2 > out
<< LIM cmd1 | cmd2 | cmd3 >> out
```  
Where in and out are files, and cmd1, cmd2, and cmd3 are shell commands.  
  
##Instructions  
  
To create the pipex program:  
`make`  
  
Usage:  
`./pipex in cmd1 cmd2 out`  
which performs:  
`< in cmd1 | cmd2 > out`  
  
Bonus features include chaining any number of commands, and using heredocs.  
To create the bonus version of pipex:  
`make bonus`  
  
Usage:  
`./pipex in cmd1 cmd2 cmd3 cmd4 ... cmdn out`  
  
Heredoc usage:  
`./pipex here_doc LIM cmd1 cmd2 ... cmdn out`  
which performs:  
`<< LIM cmd1 | cmd2 | ... | cmdn >> out`  
where LIM is any string of choice, which might be "a" for example.  
  
Note that the outfile contents are truncated when not using heredoc, and appended when using heredoc.  
  
##Resources  
  
Error codes and messages, pipe and dup2 usage:  
	what better search engine than perplexity am i right?  
	also: (
