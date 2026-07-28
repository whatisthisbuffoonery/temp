void	*death_bulb(t_args *delay, t_sem_box *box)
{
	sem_wait(box->death);
	delay->deathflag = 1;
	return (NULL);
}

//check starvation
//two more threads to increment or decrement //two more semaphores too //fml
