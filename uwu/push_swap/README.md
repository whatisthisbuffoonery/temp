*This project has been created as part of the 42 curriculum by dthoo*  
  
## Push\_swap  
  
### Resources
```  
me: to get target distance from top to use heuristics, I need relative placements
	to use the radix method, I need relative placements
	to use chunking algorithmsm, I also need relative placements

me: the only way to get relative placements...is to sort the number sequence beforehand isnt it

Perplexity: yes.

me: wtf
```  
  
### Description  
  
My goal: move around the ints in stack a until they are sorted in ascending order  
Ascending order means that the lowest int sits at the top  
  
Seeing as this is a stack organisation excercise, there is a merge sorted duplicate array at the start  
...that has then been reverted to replace the actual values with relative placements \(i.e. 0 to 100\)  
  
First, a list of problems with sorting numbers between two stacks:  
	- no random access, although I can browse the stacks whenever  
	- my actions are:  
		-	swap the top two items of a stack  
		-	transfer stuff from the top of one stack to the other in reverse order  
		-	yeet the first or last items of a stack to the other end, in same order  
		-	that's it. really.  
  
I am actually measured on these actions, rather than comparisons.  
I first need sub-problems. They are:  
	- two ints in the wrong order that have close values, may or may not be adjacent  
	- two ints in the right order that have close values, may or may not be adjacent  
	- two ints in the wrong order that have very different values  
	- two ints in the right order that have very different values  
		-	the last two multiplied by potentially having close ints on the other end  
	- bunch of consecutive ints in the right order  
	- bunch of consecutive ints in the wrong order  
	- all this multiplied by mirroring situations in stack b  
  
And I have to pick which problem to sort first, even  
  
My usage of stack b would entail:  
	- maybe storing completed parts of the sequence  
	- doing some operations  
	- 
  
So, I should organise a number of auxillary actions to take the load off of the above:  
  
Version 1:  
	- if difference between numbers is greater than 5, shunt to the other end  
	- if diff between 3 and 5 inclusive, pass to b  
	- else, take actions to sort it immediately  
	- put sorted portions in stack b  
	- when b receives a third segment, or when b takes a segment that could be merged with another, take action  
	- any time b takes a segment, check if the other items fit within and slot them in  
	- when a sees a number that should be inserted into a segment that is in b, do so  

Version 2:  
	- have number ranges to determine actions. ranges of n/10 I guess  
	- choose between sorting for ascending or descending depending on small or big numbers  
	- put smaller numbers in b  
	- when a clump of big numbers is sorted, sort them with the other numbers at the bottom of stack a  
  
Version 3:  
	- log clumps as runs, of strictly ascending values, or descending in b, of 3+ numbers  
	- group indexes into bands of n / some number  
	- if top of a is not a run, make it a run  
		-	heuristics: weigh immediate run index diff against shove down/ to b  
		-	if it can be shoved downwards or to b to extend a run, do that instead  
		-	if I have to do index difference edge cases I will cry  
	- else
		-	when b is empty, push current run to b  
		-	when b has something, merge \(two runs\)  
			-		run a < run b: ra to expose surface area, manually sort using pa/rra  
			-		run a > run b: rb/pa to insert elements  
			-		mixed values: divide runs to fit sequentially  
			-		check bottom item \(not run\) of each stack for insertions  
			-		usually merge in b  
		-	3 or 4 runs:  
			-		wont do this on purpose, but that last bottom item rule handles this  
			-		
