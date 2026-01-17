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
  
My goal: use stack instructions to sort the ints in stack A in ascending order  
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

### random notes

i can explain witholding some elements as "they would be inserted back into b in the same order, and the leftover items in a are also in the same order"

why min rotate b? because we withold an extra sequence that doesnt follow radix logic

why not max rotate a? because that is the main radix body where the buckets have to stay consistent

### 
