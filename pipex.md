## shell cant recognise open (tmp) error

main:
	in: cmd, ffd, pfd

ffd:
	no err on fd fail
	err on read / write fail
	^ double err on read / write fail

cmd:
	in: cmd, ffd


	free and close in child
	close unused pipe end in child to trigger EOF
	moved pfd cycle

	dont stop the pipeline for anything besides heredoc failure
	move physical ffd init to child
	heredoc init stays in main()
	store return code in cpid, -1 becomes 127
	on any cmd side failure, return 127
	stop execve if cmd fail, but only after fork
	wtf just move cmd to fork

 127 = "command not found" (execvp failure)
 126 = "not executable"
 2   = "misuse of shell builtin"
 1   = "shell couldn't prepare command" << malloc fail

	fuck my arse
	plssssss make a different cleanup func for child and exit that way I dowan to pass around exit code
