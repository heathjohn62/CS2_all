Forward Euler's method results in the orbiting planet spiraling off into space at orbits 
of greater and greater distance, and the ball eventually leaves the screen entirely. The
energy appears to steadily increase for this method. 

Backwards Eulers method has the opposite result, the planet makes smaller and 
smaller, roughly circular orbits until it is swallowed by the large planet. The energy 
appears to steadily decrease for this method. 

Symplectic Euler's method seems to function the best as an approximation for an
elliptic orbit. Here, the planet makes routine elliptic orbits around the large planet, 
but doesn't seem (on short timescales at least) to get much further away, or to 
actually hit the large planet. The energy for this method oscillates between -.5 and -.48, 
and the fact that it seems not shift in either direction is further proof that this is the 
best approximation. 
