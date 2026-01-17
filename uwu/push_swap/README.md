*This project has been created as part of the 42 curriculum by dthoo*  
  
## Push\_swap  
  
### Resources
```  
me: to get target distance from top to use heuristics, I need relative placements
	to use the radix method, I need relative placements
	to use chunking algorithmsm, I also need relative placements

me: the only way to get relative placements...is to sort the number sequence beforehand isnt it

Perplexity: yes.

me: bruh
```  
  
greedy insertion: (https://pure-forest.medium.com/push-swap-turk-algorithm-explained-in-6-steps-4c6650a458c0)  
greedy insertion optimisation: toss that 'bound' integer out the window and search for candidates from either side of stack b. Automatic butterfly chunking!  
lsd radix: (https://medium.com/nerd-for-tech/push-swap-tutorial-fa746e6aba1e)  
lsd radix keep-in-b idea: (https://github.com/hu8813/push_swap/blob/main/src/sort.c)  
msd radix: my idea actually. It serves as a rather lazy method of chunking that:  
	- requires no knowledge of what the initial sample size was  
	- does no delta calculations, almost half of the numbers are in good chunks. The other half is split between the smallest and second smallest number chunks  
	- uses what I imagine as rather few moves to achieve what it does  
  
### Description  
  
My goal: use stack instructions to sort the numbers in stack A in ascending order  
Ascending order means that the lowest number sits at the top  
  
Seeing as this is a stack organisation excercise, there is a merge sorted duplicate array at the start  
that has then been reverted to replace the actual values with relative placements \(i.e. 0 to 100\)  
  
First, a list of problems with sorting numbers between two stacks:  
	- no random access, although I can browse the stacks whenever  
	- my actions are:  
		-	swap the top two items of a stack  
		-	transfer stuff from the top of one stack to the other in reverse order  
		-	yeet the first or last items of a stack to the other end, in same order  
		-	that's it. really.  
  
For my project, I use radix methods and greedy insertion  
  
n = 100 benchmark: 600  
n = 500 benchmark: 3900 ~ 4300  
  
### Instructions  
  
'make' builds push\_swap  
'make bonus' builds the checker  
