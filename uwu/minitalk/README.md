uh

I dont 

well

my current model:

client pauses() initially

server logically cant handle senamtics, so it wont

server sends out sig2 on 10ms intervals to indicate empty queue

20 uninterrupted sig2 means server is waiting

client replies with loud sig1, 5ms \+ \(10ms \* pid/10000\) delay//32bit pid assumption
!!have TDM concepts but no guarantees, i aint evaling this shi
	- pause on occupied response: other sig1s before sending own response
		-	if single loud sig2 within 10ms  else, start sending
		-	else if 3 sig2s, dig further into pid no and try again
			-		those that heard a sig1 before sending do not participate, go back to pause
				-			self determine if self is at front of queue, have bypass for other clients going offline

client sends bytes in 1ms intervals and waits for single sig2 ack

this project sucks
