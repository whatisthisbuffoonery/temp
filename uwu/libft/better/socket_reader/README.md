linked lists are useful for many sources of inconsistent reads
gnl reads out of disk storage, not a network connection
hence, this folder is no longer a gnl attempt

perplexity says limit the capacity of each fd for basic security

also put a tail pointer per fd pls


idea of this method is that the caller wants to micromanage buffers
in exchange for not having a buffer double itself past the available RAM

so, the reader will export a linked list
