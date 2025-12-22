*This project has been created as part of the 42 curriculum by dthoo*  
  
## Get Next Line  
  
### Description  
  
The get\_next\_line function reads a line out of a file, or stdin  
Returns NULL on read error, empty/fully read file, or failure to open a file  
Buffer size can be changed at compile time  
  
### Instructions  
  
cc -Wall -Wextra -Werror get\_next\_line.c get\_next\_line\_utils.c  
  
### Resources  
  
None, really  
I did prompt AI to get the bonus started but  I thought that the constraint made this project not worth it  
  
### How it works  
  
Take a fd  
Keep trying to read from it  
If it makes a list by the end, parse it  
Return null or a string  
Partial reads are accounted for  
  
### Partial reads  
  
Occasions where read() reads less then buf\_size before EOF for whatever reason  
This does not happen very often, but I got to simulate this inadvertently with funny node sizes  
So, I now count each string length individually  
