cat << 'a' | ./a.out >> poop

cat reads blocking input from <<, stopping at line exactly matching 'a'

cat's output is piped to a.out, then that is written to poop

do block for heredoc
