realloc

it loops over LESS chars than using a linked list:\
n(final read) + log2(n)(all the reallocs prior)\
vs\
n(finding '\n') + n(exporting from linked list to string)

the signal idea from before is still neat
