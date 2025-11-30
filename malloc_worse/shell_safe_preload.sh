echo "realpath is a real command"
export LD_PRELOAD=$(realpath malloc_worse.so)
