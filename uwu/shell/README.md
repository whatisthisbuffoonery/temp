this says signal actions:
https://pubs.opengroup.org/onlinepubs/7908799/xsh/signal.h.html

we prolly just use sigaction

echo uses just one dash to absorb all flags, including duplicates. so:
	echo -eeeeeeeeeeeeeeeeeeeeeennnnnnnnnnnnnnnn is acceptable
	check the other builtins too

no set builtin means no set pipefail. then again my teammate is not handling children

handle 2>

handle quote waiting (pipes should be big enough)

env parsing is just like argv parsing

readline can differentiate quotes
	error log for command not found displays backslash n
	newline not treated as whitespace

signals: if input has anything at that point, behaviour is quite different
	ctrl d does nothing if input has text
		ctrl d in a heredoc needs to emit "match not found" warning
	ctrl backslash does nothing unless a child is running, it quits that
	ctrl c is just ctrl c
	all of these can bork return values differently

ctrl c should not add half typed input to history

elkan and yiyuan forgor to exclude empty inputs from history (possibly being just nl)

$? not a env var, store in shell for later retrieval

perplexity says env is a node list, say hello to 10 init files jackass

handle "shell variable", something akin to push swap where the assignment is forgotten is 0.1seconds

quote handling is, thankfully, left to right (ignore quotes of different types too)

not asked to handle any other syntax symbols

this project lives and dies by error reporting

builtin with no options does not mean no args

expand $vars before checking for commands
	env vars cannot contain special identifiers:
		$?    → last exit status
		$$    → current PID  
		$!    → last background PID
		$0    → script name
		$#    → argument count
		$@ $\*, positional parameters (1-9, ${10}+)
			these are for args given to shell scripts
			check for shebang assignment, fall back to calling bash to settle it
		$-    → shell options flags
		$_    → last argument of previous command

why tf would I use fstat
	why tf would I reach into bash to borrow shell printf

cd dash returns you to the last dir you were at (init to ~) and prints a message detailing the new current dir (~/thing, or if not, abs path)

volatile sig value it is

do remember to ignore leading whitespace in front of command, run it anyway

&& and || blindly use the last exit status they got
	pipelines count as one command in this case

redirection assumes stdin/out, number and redirection without space says filenumber
	1> for out, 0< for in
		cat 0< file vomits the file
			echo never pays attention to stdin, heredocs are the shell's problem
	this will be mildly irritating

ctrl underscore nitpick

wth is a subshell and how do you replicate it

ctrl c stops the whole command pipeline

just pass globstars \* into argv as is

history features:
!!           → last command
!n           → history line n
!string      → most recent command starting with "string"
!?string[?]  → most recent containing "string"
!$           → last argument of previous command
!:N          → Nth arg of previous command
!:1-3        → args 1-3 of previous command
!:1*         → arg 1 + all after

sigint stuct to code 130 and sigquit to 131

bash will init all heredocs regardless, bash will not init pipes unless truthy

go see if the systems have flex and bison

history inside heredocs should be present

use different handlers for flagging interrupt and fiddling with readline, rl_signal_event_hook

improper syntax just return 1

quotes stop whitespace from being ignored

--------------------------------------------

|VETO| I need a linked list for history management. Not for arrow keys, but for '!' expansion
|VETO| I need to interpret brackets
globstars for all dirs? perplex lied, I have to glob manually
redirection ok
still keep 
